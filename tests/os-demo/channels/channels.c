/*
 * Imported from the operating systems class.
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "../utils/utils.h"

static void msg_and_wait(const char *msg)
{
	char buf[256];

	puts(msg);
	fputs("	 Continuing ...\n", stdout); fflush(stdout);
	sleep(1);
}

int main(void)
{
	int fd1, fd2, sockfd1, sockfd2, sockfd3, pipefd[2];

	msg_and_wait("before open fd1");
	fd1 = open("/etc/hosts", O_RDONLY);

	msg_and_wait("before open fd2");
	fd2 = open("/etc/passwd", O_RDONLY);

	msg_and_wait("before sockfd1");
	sockfd1 = socket(PF_INET, SOCK_STREAM, 0);

	msg_and_wait("before sockfd2");
	sockfd2 = socket(PF_INET, SOCK_DGRAM, 0);

	msg_and_wait("before pipe");
	pipe(pipefd);

	msg_and_wait("before close fd2");
	close(fd2);

	msg_and_wait("before sockfd3");
	sockfd3 = socket(PF_UNIX, SOCK_STREAM, 0);

	msg_and_wait("before end");

	return 0;
}
