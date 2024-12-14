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
#define BUFSIZ		256
#endif


static pid_t create_process(const char *path)
{
	pid_t pid;
	int rc;

	pid = fork();
	pid = fork();
	printf("aaa\n");
	switch (pid) {
	case -1:	/* error */
		DIE(pid < 0, "fork");
		break;

	case 0:		/* child process */
		rc = execl(path, path, NULL);
		DIE(rc < 0, "execl");
		break;

	default:	/* parent process */
		break;
	}

	return pid;
}


int main(void)
{
	/* Create child process. Ignore PID return value. */
	create_process("./printer");

	/* Wait for child process. */
	wait(NULL);

	return 0;
}
