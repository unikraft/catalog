/*
 * Imported from the operating systems class.
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#include "../utils/utils.h"

static int data_var = 0;

static void inc(void)
{
	data_var++;
	printf("data_var = %d\n", data_var);
}

int main(void)
{
	int status;
	pid_t pid = fork();

	switch (pid) {
	case -1:
		DIE(pid, "fork");
	case 0:
		/* child process */
		inc();
		break;
	default:
		/* parent process */
		sleep(2);
		inc();
		wait(&status);
		break;
	}

	return 0;
}
