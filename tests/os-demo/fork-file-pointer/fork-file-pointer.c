/*
 * Imported from the operating systems class.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/wait.h>

#include "../utils/utils.h"

int main(void)
{
	pid_t pid;
	int fd;
	ssize_t ret;

	fd = open("f.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	DIE(fd < 0, "open");

	sleep(5);

	ret = write(fd, "0000000000", 10);
	DIE(ret < 0, "write");

	sleep(5);

	pid = fork();
	switch (pid) {
	case -1:	/* error */
		DIE(pid == -1, "fork");

	case 0:		/* child process */
		ret = write(fd, "1111111111", 10);
		DIE(ret < 0, "write");

		sleep(5);

		exit(EXIT_SUCCESS);
		break;

	default:	/* parent process */
		break;
	}

	/* Only parent process reaches this point. */

	/* Wait for child process. Don't care about exit status. */
	ret = waitpid(pid, NULL, 0);
	DIE(ret < 0, "waitpid");

	ret = write(fd, "2222222222", 10);
	DIE(ret < 0, "write");

	sleep(5);
	printf("Success!\n");

	return 0;
}
