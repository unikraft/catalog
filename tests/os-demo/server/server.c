/*
 * Simple file server.
 *
 * Operating Systems, 2014
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
#define BUFSIZE			100000

/*
 * "upgraded" read routine
 */

static ssize_t xread(int fd, void *buffer, size_t len)
{
	ssize_t ret;
	ssize_t n;

	n = 0;
	while (n < (ssize_t)len) {
		ret = read(fd, (char *)buffer + n, len - n);
		if (ret < 0)
			return -1;
		if (ret == 0)
			break;
		n += ret;
	}

	return n;
}

/*
 * "upgraded" write routine
 */

static ssize_t xwrite(int fd, const void *buffer, size_t len)
{
	ssize_t ret;
	ssize_t n;

	n = 0;
	while (n < (ssize_t)len) {
		ret = write(fd, (const char *) buffer + n, len - n);
		if (ret < 0)
			return -1;
		if (ret == 0)
			break;
		n += ret;
	}

	return n;
}

/*
 * "upgraded" recv routine
 */

static ssize_t xrecv(int s, void *buffer, size_t len)
{
	return xread(s, buffer, len);
}

/*
 * "upgraded" send routine
 */

static ssize_t xsend(int s, const void *buffer, size_t len)
{
	return xwrite(s, buffer, len);
}

/*
 * Handle a new connection request on the server socket.
 */

static int accept_connection(int listenfd)
{
	int sockfd;
	socklen_t addrlen = sizeof(struct sockaddr_in);
	struct sockaddr_in addr;

	/* Accept new connection. */
	sockfd = accept(listenfd, (SSA *) &addr, &addrlen);
	DIE(sockfd < 0, "accept");

	dlog(LOG_INFO, "Accepted connection from %s:%d\n",
		inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));

	return sockfd;
}

static int receive_filename(int s, char *buffer, size_t len)
{
	ssize_t n;
	int valid = 1;

	n = xrecv(s, buffer, len);
	if (n < 0) {
		valid = -1;
	} else {
		if (buffer[n-1] != '\n')
			valid = 0;
		else
			buffer[n-1] = '\0';
	}
	if (valid)
	  printf("%s\n", buffer);
	else
	  printf("Got wrong fn\n");

	return valid;
}

static int serve_file(int s, const char *fname)
{
	char buffer[BUFSIZE];
	ssize_t n, n2;
	int fd;
	int err = 0;

	fd = open(fname, O_RDONLY);
	if (fd < 0) {
		ERR("open");
		goto bad_file;
	}

	while (1) {
		n = read(fd, buffer, BUFSIZE);
		if (n < 0) {
			ERR("read");
			goto bad_read;
		}
		if (n == 0)
			break;

		n2 = xsend(s, buffer, n);
		if (n2 < 0) {
			ERR("send");
			goto bad_send;
		}
	}

	close(fd);
out:
	return err;

bad_send:
bad_read:
	close(fd);
bad_file:
	err = -1;
	goto out;
}

int main(void)
{
	int listenfd;	/* server socket file descriptor */
	int connectfd;	/* connection socket */
	int valid;	/* is request valid */
	char fname[256];

	/* Create server socket. */
	listenfd = tcp_create_listener(LISTEN_PORT, DEFAULT_LISTEN_BACKLOG);
	DIE(listenfd < 0, "tcp_create_listener");

	/* server main loop */
	while (1) {
		connectfd = accept_connection(listenfd);
		valid = receive_filename(connectfd, fname, 9);
		if (valid)
			serve_file(connectfd, fname);
		close(connectfd);
	}

	return 0;
}
