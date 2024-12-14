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
#define BUFSIZ	  256
#endif


static pid_t create_process_with_redirect(const char *path, int new_stdin,
										  int new_stdout, int new_stderr)
{
	pid_t pid;
	int rc;

	pid = fork();
	switch (pid) {
	case -1:	/* error */
		DIE(pid < 0, "fork");
		break;

	case 0:		/* child process */
		if (new_stdin != -1)
			dup2(new_stdin, 0);
		if (new_stdout != -1)
			dup2(new_stdout, 1);
		if (new_stderr != -1)
			dup2(new_stderr, 2);

		rc = execl(path, path, NULL);
		DIE(rc < 0, "execl");
	}

	return pid;
}


int main(void)
{
	int pipefd[2];
	int rc;

	rc = pipe(pipefd);
	DIE(rc < 0, "pipe");

	/* Create child processes. Ignore PID return value. */
	create_process_with_redirect("./reader", pipefd[0], -1, -1);
	create_process_with_redirect("./writer", -1, pipefd[1], -1);

	/* Only child processess use pipe. */
	close(pipefd[0]);
	close(pipefd[1]);

	/* Wait for child processes. */
	wait(NULL);
	wait(NULL);

	return 0;
}
