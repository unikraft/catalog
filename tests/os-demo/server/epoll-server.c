/*
 * epoll-based file server. Uses epoll(7) to multiplex connections.
 * 
 * TODO:
 *  - block data receiving when receive buffer is full (use circular buffers)
 *  - do not copy receive buffer into send buffer when send buffer data is
 *	  still valid
 *
 * 2011, Operating Systems
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "./util.h"
#include "./debug.h"
#include "./sock-util.h"
#include "./w_epoll.h"

#define LISTEN_PORT		42424
#define BUFSIZE			10

/* server socket file descriptor */
static int listenfd;

/* epoll file descriptor */
static int epollfd;

enum connection_state
{
	STATE_INIT,
	STATE_RECEIVE_DATA,
	STATE_FILENAME_RECEIVED,
	STATE_READ_DATA,
	STATE_SEND_DATA,
	STATE_ALL_DATA_READ,
	STATE_CONNECTION_ERROR,
};

/* structure acting as a connection handler */
struct connection {
	int sockfd;
	char filename[256];
	size_t bytes_recv;
	char sock_send_buffer[BUFSIZ];
	size_t bytes_read;
	size_t bytes_sent;
	enum connection_state state;
	int fd;
};

/*
 * Initialize connection structure on given socket.
 */

static struct connection *create_connection(int sockfd)
{
	struct connection *conn = malloc(sizeof(*conn));
	DIE(conn == NULL, "malloc");

	conn->sockfd = sockfd;
	memset(conn->filename, 0, 256);
	memset(conn->sock_send_buffer, 0, BUFSIZ);
	conn->bytes_recv = 0;
	conn->bytes_read = 0;
	conn->bytes_sent = 0;
	conn->state = STATE_INIT;
	conn->fd = -1;

	return conn;
}

/*
 * Remove connection handler.
 */

static void remove_connection(struct connection *conn)
{
	w_epoll_remove_ptr(epollfd, conn->sockfd, conn);
	close(conn->sockfd);
	close(conn->fd);
	free(conn);
}

/*
 * Handle a new connection request on the server socket.
 */

static void handle_new_connection(void)
{
	static int sockfd;
	socklen_t addrlen = sizeof(struct sockaddr_in);
	struct sockaddr_in addr;
	struct connection *conn;
	int rc;

	/* Accept new connection. */
	sockfd = accept(listenfd, (SSA *)&addr, &addrlen);
	if (sockfd < 0) {
		ERR("accept");
		return;
	}

	dlog(LOG_ERR, "Accepted connection from: %s:%d\n",
			inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));

	/* Instantiate new connection handler. */
	conn = create_connection(sockfd);

	/* Add socket to epoll. Wait for input (filename to serve). */
	rc = w_epoll_add_ptr_in(epollfd, sockfd, conn);
	if (rc < 0) {
		ERR("w_epoll_add_in");
		remove_connection(conn);
	}
}

/*
 * Receive message on socket.
 * Store filename in filename field in struct connection.
 */

static void receive_message(struct connection *conn)
{
	ssize_t bytes_recv;
	int rc;
	char abuffer[64];

	rc = get_peer_address(conn->sockfd, abuffer, 64);
	if (rc < 0) {
		ERR("get_peer_address");
		conn->state = STATE_CONNECTION_ERROR;
		return;
	}
	bytes_recv = recv(conn->sockfd, conn->filename + conn->bytes_recv,
									BUFSIZ - conn->bytes_recv, 0);
	if (bytes_recv < 0) {		/* error in communication */
		dlog(LOG_ERR, "Error in communication from: %s\n", abuffer);
		conn->state = STATE_CONNECTION_ERROR;
		return;
	}
	if (bytes_recv == 0) {		/* connection closed */
		dlog(LOG_INFO, "Connection closed from: %s\n", abuffer);
		conn->state = STATE_FILENAME_RECEIVED;
		return;
	}

	dlog(LOG_DEBUG, "Received message from: %s\n", abuffer);
	dlog(LOG_DEBUG, "Message received is: %s\n", conn->filename);

	conn->bytes_recv += bytes_recv;
	conn->state = STATE_RECEIVE_DATA;
	if (strchr(conn->filename, '\n') != NULL)
		conn->state = STATE_FILENAME_RECEIVED;
}

/*
 * Receive filename.
 */

static void receive_filename(struct connection *conn) 
{
	int rc;

	/* If error (STATE_CONNECTION_ERROR), remove connection. */
	receive_message(conn);
	if (conn->state == STATE_CONNECTION_ERROR)
		goto error;

	/* When filename is received, only accept out events. */
	if (conn->state == STATE_FILENAME_RECEIVED) {
		if (conn->filename[conn->bytes_recv-1] != '\n') {
			fprintf(stderr, "No newline in filename.\n");
			goto error;
		}
		conn->filename[conn->bytes_recv-1] = '\0';
		rc = w_epoll_update_ptr_out(epollfd, conn->sockfd, conn);
		if (rc < 0) {
			ERR("w_epoll_add_ptr_out");
			goto error;
		}
	}

	return;
error:
	remove_connection(conn);
}

static void open_file(struct connection *conn)
{
	if (conn->fd < 0) {
		conn->fd = open(conn->filename, O_RDONLY);
		if (conn->fd < 0) {
			ERR("open");
			conn->state = STATE_CONNECTION_ERROR;
			return;
		}
	}
	conn->state = STATE_READ_DATA;
}

static void read_file(struct connection *conn)
{
	ssize_t bytes_read;

	bytes_read = read(conn->fd, conn->sock_send_buffer, BUFSIZE);
	if (bytes_read < 0) {
		ERR("read");
		conn->state = STATE_CONNECTION_ERROR;
		return;
	}
	/* Close connection in case all data is read. */
	if (bytes_read == 0) {
		conn->state = STATE_ALL_DATA_READ;
		return;
	}
	conn->bytes_read = bytes_read;
	conn->bytes_sent = 0;
	conn->state = STATE_SEND_DATA;
}

/*
 * Send message on socket.
 * Store message in sock_send_buffer in struct connection.
 */

static void send_message(struct connection *conn)
{
	ssize_t bytes_sent;
	int rc;
	char abuffer[64];

	rc = get_peer_address(conn->sockfd, abuffer, 64);
	if (rc < 0) {
		ERR("get_peer_address");
		goto error;
	}

	bytes_sent = send(conn->sockfd, conn->sock_send_buffer + conn->bytes_sent,
									conn->bytes_read - conn->bytes_sent, 0);
	if (bytes_sent < 0) {
		dlog(LOG_ERR, "Error in communication to %s\n", abuffer);
		goto error;
	}
	if (bytes_sent == 0) {
		dlog(LOG_INFO, "Connection closed to %s\n", abuffer);
		goto error;
	}

	conn->bytes_sent += bytes_sent;
	if (conn->bytes_sent >= conn->bytes_read)
		conn->state = STATE_READ_DATA;
	return;

error:
	conn->state = STATE_CONNECTION_ERROR;
}

static void serve_file(struct connection *conn)
{
	switch (conn->state) {
	case STATE_FILENAME_RECEIVED:
		open_file(conn);
		if (conn->state == STATE_CONNECTION_ERROR)
			goto error;
		/* Flow through. Having no 'break' statement is a feature. */

	case STATE_READ_DATA:
		read_file(conn);
		if (conn->state == STATE_CONNECTION_ERROR ||
				conn->state == STATE_ALL_DATA_READ)
			goto error;
		/* Flow through. Having no 'break' statement is a feature. */

	case STATE_SEND_DATA:
		send_message(conn);
		if (conn->state == STATE_CONNECTION_ERROR)
			goto error;
		break;

	default:
		goto error;
	}

	return;

error:
	remove_connection(conn);
}

int main(void)
{
	int rc;

	/* Init multiplexing. */
	epollfd = w_epoll_create();
	DIE(epollfd < 0, "w_epoll_create");

	/* Create server socket. */
	listenfd = tcp_create_listener(LISTEN_PORT, DEFAULT_LISTEN_BACKLOG);
	DIE(listenfd < 0, "tcp_create_listener");

	rc = w_epoll_add_fd_in(epollfd, listenfd);
	DIE(rc < 0, "w_epoll_add_fd_in");

	dlog(LOG_INFO, "Server waiting for connections on port %d\n", LISTEN_PORT);

	/* server main loop */
	while (1) {
		struct epoll_event rev;

		/* Wait for events. */
		rc = w_epoll_wait_infinite(epollfd, &rev);
		DIE(rc < 0, "w_epoll_wait_infinite");

		/*
		 * Switch for event types; consider
		 *   - new connection requests (on server socket)
		 *   - socket communication (on connection sockets)
		 */

		if (rev.data.fd == listenfd) {
			dlog(LOG_DEBUG, "New connection\n");
			if (rev.events & EPOLLIN)
				handle_new_connection();
		} else {
			if (rev.events & EPOLLIN) {
				dlog(LOG_DEBUG, "New message\n");
				receive_filename(rev.data.ptr);
			}
			if (rev.events & EPOLLOUT)
				serve_file(rev.data.ptr);
		}
	}

	return 0;
}
