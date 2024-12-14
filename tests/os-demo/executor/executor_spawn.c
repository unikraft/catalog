/*
 * Imported from the operating systems class.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <spawn.h>
#include "../utils/utils.h"


static pid_t create_process(const char *path)
{
	pid_t pid;
	int ret;
	char *args[] = {path, NULL};

	ret = posix_spawn(&pid, path, NULL, NULL, args, NULL);
	if (ret < 0) {
		perror("posix_spawn");
		exit(EXIT_FAILURE);
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
