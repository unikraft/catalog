/*
 * Imported from the operating systems class.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

#include "../utils/utils.h"

#define BUFSIZE		1024

static char buffer[BUFSIZE] = { '1', };

static void msg_and_wait(const char *msg)
{
	char buf[256];

	puts(msg);
	fputs("	 Continuing ... ", stdout); fflush(stdout);
	sleep(2);
}

int main(void)
{
	int fd;
	ssize_t n;
	int ret;

	msg_and_wait("started program");

	fd = open("f.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
	DIE(fd < 0, "open");
	msg_and_wait("opened f.txt");

	n = write(fd, buffer, BUFSIZE);
	DIE(n < 0, "write");
	msg_and_wait("written 1024 bytes");

	n = lseek(fd, -512, SEEK_CUR);
	DIE(n < 0, "lseek");
	msg_and_wait("went backwards 512 bytes");

	n = read(fd, buffer, 256);
	DIE(n < 0, "read");
	msg_and_wait("read 256 bytes");

	ret = ftruncate(fd, 256);
	DIE(ret < 0, "ftruncate");
	msg_and_wait("truncated file to 256 bytes");

	close(fd);
	msg_and_wait("closed files");

	return 0;
}
