/*
 * Imported from the operating systems class.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "../utils/utils.h"


#define LISTEN_PORT		5000
#define LISTEN_BACKLOG	5


static const char MSG[] = "Called actual function.\n\n";
static const char ATTACK[]  = "Called injected function.\n\n";
static int connectfd;


static void actual_func(void)
{
	write(connectfd, MSG,  strlen(MSG)+1);
}

static void inject_func(void)
{
	write(connectfd, ATTACK, strlen(ATTACK)+1);
}

static void process_client(void)
{
	char buffer[16];

	read(connectfd, buffer, 100);
}


int main(void)
{
	int listenfd;
	struct sockaddr_in servaddr;
	int rc;
	pid_t pid;

	/* Create TCP (stream) socket. */
	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	DIE(listenfd < 0, "socket");
	memset(&servaddr, 0, sizeof(servaddr));

	/* Assign IP address and port to socket. */
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(LISTEN_PORT);

	/* Put server socket in listening mode. */
	rc = bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
	DIE(rc < 0, "bind");
	rc = listen(listenfd, LISTEN_BACKLOG);
	DIE(rc < 0, "listen");

	while (1) {
		/* Loop waiting for connections. Ignore originating address. */
		connectfd = accept(listenfd, NULL, 0);
		DIE(connectfd < 0, "accept");
		pid = fork();
		switch (pid) {
		case 0:	/* child process */
			process_client();
			actual_func();
			close(connectfd);
			exit(EXIT_SUCCESS);
			break;

		default: /* parent process or error */
			close(connectfd);
			wait(NULL);	/* ignore child exit status */
		}
	}

	return 0;
}
