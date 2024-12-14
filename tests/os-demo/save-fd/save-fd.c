/*
 * Imported from the operating systems class.
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "../utils/utils.h"

int main(void)
{
	int ret;
	int fd;

	fd = open("bogdan.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
	DIE(fd < 0, "open");

	ret = dup2(1, 42);
	DIE(ret < 0, "dup2");

	ret = dup2(fd, 1);
	DIE(ret < 0, "dup2");

	write(1, "ana are mere\n", 13);
	dup2(42, 1);
	write(1, "alin nu are mere\n", 17);

	close(fd);

	return 0;
}
