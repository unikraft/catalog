/*
 * Imported from the operating systems class.
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "../utils/utils.h"

#define FILENAME		"fake-gargantua.dat"
#define SIZE_TO_TRUNCATE	(2048UL*1024*1024)	/* 2GB */

int main(void)
{
	int fd;
	int ret;
	struct stat sbuf;

	fd = open(FILENAME, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	DIE(fd < 0, "open");

	ret = ftruncate(fd, SIZE_TO_TRUNCATE);
	DIE(ret < 0, "ftruncate");

	ret = fstat(fd, &sbuf);
	DIE(ret < 0, "ftruncate");

	printf("file size is: %ld\n", sbuf.st_size);
	printf("number of blocks is: %ld\n", sbuf.st_blocks);

	return 0;
}
