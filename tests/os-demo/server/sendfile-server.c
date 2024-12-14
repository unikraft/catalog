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
#include <sys/sendfile.h>

#include "./util.h"
#include "./debug.h"
#include "./sock-util.h"
#include "./w_epoll.h"

#define LISTEN_PORT		42424
#define BUFSIZE			10

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
 * "upgraded" recv routine
 */

static ssize_t xrecv(int s, void *buffer, size_t len)
{
	return xread(s, buffer, len);
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
	sockfd = accept(listenfd, (SSA *)&addr, &addrlen);
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

	return valid;
}

static int serve_file(int s, const char *fname)
{
	int fd;
	int err = 0;
	int rc;
	struct stat sbuf;

	fd = open(fname, O_RDONLY);
	if (fd < 0) {
		ERR("open");
		goto bad_file;
	}
	rc = fstat(fd, &sbuf);
	if (rc < 0) {
		ERR("fstat");
		goto bad_fstat;
	}
	rc = sendfile(s, fd, NULL, sbuf.st_size);
	if (rc < 0) {
		ERR("sendfile");
		goto bad_sendfile;
	}

	close(fd);
out:
	return err;

bad_sendfile:
bad_fstat:
	close(fd);
bad_file:
	err = -1;
	goto out;
}

int main(void)
{
	int listenfd;	/* server socket file descriptor */
	int connectfd;   /* connection socket */
	int valid;	   /* is request valid */
	char fname[256];

	/* Create server socket. */
	listenfd = tcp_create_listener(LISTEN_PORT, DEFAULT_LISTEN_BACKLOG);
	DIE(listenfd < 0, "tcp_create_listener");

	/* server main loop */
	while (1) {
		connectfd = accept_connection(listenfd);
		valid = receive_filename(connectfd, fname, 256);
		if (valid)
			serve_file(connectfd, fname);
		close(connectfd);
	}

	return 0;
}
