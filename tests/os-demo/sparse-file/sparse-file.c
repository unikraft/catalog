/*
 * Imported from the operating systems class.
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "../utils/utils.h"

#define FILENAME		"sparse.dat"

static char buffer[1024];

int main(void)
{
	int fd;
	int ret;

	memset(buffer, 'A', 1024);

	fd = open(FILENAME, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	DIE(fd < 0, "open");

	ret = write(fd, buffer, 1024);
	DIE(ret < 0, "write");

	ret = lseek(fd, 1024, SEEK_END);
	DIE(ret < 0, "lseek");

	ret = write(fd, buffer, 1024);
	DIE(ret < 0, "write");

	ret = lseek(fd, 1024, SEEK_END);
	DIE(ret < 0, "lseek");

	ret = write(fd, buffer, 1024);
	DIE(ret < 0, "write");

	return 0;
}
