/*
 * Imported from the operating systems class.
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "../utils/utils.h"

static void msg_and_wait(const char *msg)
{
	char buf[256];

	puts(msg);
	fputs("	 Continuing ...\n", stdout); fflush(stdout);
	sleep(1);
}

int main(void)
{
	int fd1, fd2, rc, pos;

	msg_and_wait("open start");

	fd1 = open("Makefile", O_RDWR);
	DIE(fd1 < 0, "open file.txt");
	msg_and_wait("first open Makefile");

	fd2 = open("Makefile", O_RDWR);
	DIE(fd1 < 0, "open file.txt");
	msg_and_wait("second open Makefile");

	pos = lseek(fd1, 100, SEEK_SET);
	DIE(pos < 0, "lseek");
	msg_and_wait("lseek on fd1");

	rc = close(fd1);
	DIE(rc < 0, "fd1");
	msg_and_wait("close fd1");

	rc = close(fd2);
	DIE(rc < 0, "fd2");
	msg_and_wait("close fd2");

	return 0;
}
