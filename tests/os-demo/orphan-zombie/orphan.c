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

	pid = fork();
	switch (pid) {
	case -1:	/* error */
		DIE(pid == -1, "fork");

	case 0:	 /* child process */
		printf("  [child] Parent is not dead. PPID is %d.\n", getppid());
		sleep(10);
		printf("  [child] Parent is dead. PPID is %d.\n", getppid());
		exit(EXIT_SUCCESS);
		break;

	default:	/* parent process */
		break;
	}

	/* Sleep to sync with child process then exit. */
	sleep(5);

	return 0;
}
