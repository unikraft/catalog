/*
 * Imported from the operating systems class.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include "../utils/utils.h"


#ifndef BUFSIZ
#define BUFSIZ  256
#endif


int main(void)
{
	int pipefd[2];
	const char *send_msg =  "Take care, my son.";
	char recv_buf[BUFSIZ];
	pid_t pid;
	int rc;

	rc = pipe(pipefd);
	DIE(rc < 0, "pipe");

	pid = fork();
	switch (pid) {
	case -1:	/* error */
		DIE(pid < 0, "fork");
		break;

	case 0:		/* Child process is receiver. */
		/* Receiver doesn't need pipe write end. */
		close(pipefd[1]);

		/* Make stdin file descriptor point to pipe read end. */
		close(0);
		dup(pipefd[0]);

		/*
		 * Pipe read end is pointed to by stdin file
		 * descriptor. No need for original file descriptor.
		 */
		close(pipefd[0]);

		read(0, recv_buf, BUFSIZ);
		printf("Client received message: \"%s\"\n", recv_buf);

		return 0;

	default:	/* Parent process is sender. */
		sleep(3);
		/* Sender doesn't need pipe read end. */
		close(pipefd[0]);
		/* Make stdout file descriptor point to pipe read end. */
		dup2(pipefd[1], 1);

		/*
		 * Pipe write end is pointed to by stdout file
		 * descriptor. No need for original file descriptor.
		 */
		close(pipefd[1]);

		write(1, send_msg, strlen(send_msg) + 1);

		wait(NULL);
	}

	return 0;
}
