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
#include <pthread.h>

#include "./util.h"
#include "./debug.h"
#include "./sock-util.h"
#include "./w_epoll.h"

#define LISTEN_PORT		42424
#define BUFSIZE			8192

static struct {
#define BAG_EMPTY_SIZE		0
#define BAG_FULL_SIZE		16
	int buffer[BAG_FULL_SIZE];
	int size;
	pthread_mutex_t mutex;
	pthread_cond_t empty_cond;
	pthread_cond_t full_cond;
} bag;

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

static void add_to_bag(int s)
{
	pthread_mutex_lock(&bag.mutex);
	while (bag.size == BAG_FULL_SIZE)
		pthread_cond_wait(&bag.full_cond, &bag.mutex);
	bag.buffer[bag.size] = s;
	bag.size++;
	pthread_cond_signal(&bag.empty_cond);
	pthread_mutex_unlock(&bag.mutex);
}

static int remove_from_bag(void)
{
	int s;

	pthread_mutex_lock(&bag.mutex);
	while (bag.size == BAG_EMPTY_SIZE)
		pthread_cond_wait(&bag.empty_cond, &bag.mutex);
	bag.size--;
	s = bag.buffer[bag.size];
	pthread_cond_signal(&bag.full_cond);
	pthread_mutex_unlock(&bag.mutex);

	return s;
}


/* Thread function: Read socket from bag and process. Repeat forever. */
static void *thread_serve(void *arg)
{
	int sockfd;
	int valid;	/* is request valid */
	char fname[256];

	while (1) {
		sockfd = remove_from_bag();
		valid = receive_filename(sockfd, fname, 9);
		if (valid)
			serve_file(sockfd, fname);
		close(sockfd);
	}

	return NULL;
}

static void init_bag(void)
{
	memset(bag.buffer, 0, BAG_FULL_SIZE);
	bag.size = 0;
	pthread_mutex_init(&bag.mutex, NULL);
	pthread_cond_init(&bag.empty_cond, NULL);
	pthread_cond_init(&bag.full_cond, NULL);
}

static void create_threads(void)
{
	pthread_t *tids;
	int nprocs;
	size_t i;

	nprocs = sysconf(_SC_NPROCESSORS_ONLN);
	if (nprocs < 0) {
		perror("sysconf");
		exit(EXIT_FAILURE);
	}

	tids = malloc(nprocs * sizeof(*tids));
	for (i = 0; i < (size_t)nprocs; i++)
		if (pthread_create(&tids[i], NULL, thread_serve, NULL) != 0) {
			perror("pthread_create");
			exit(EXIT_FAILURE);
		}
}

int main(void)
{
	int listenfd;	/* server socket file descriptor */
	int connectfd;	/* connection socket */

	/* Initialize bag of tasks. */
	init_bag();

	/* Create worker threads. */
	create_threads();

	/* Create server socket. */
	listenfd = tcp_create_listener(LISTEN_PORT, DEFAULT_LISTEN_BACKLOG);
	DIE(listenfd < 0, "tcp_create_listener");

	/* server main loop */
	while (1) {
		connectfd = accept_connection(listenfd);
		add_to_bag(connectfd);
	}

	return 0;
}
