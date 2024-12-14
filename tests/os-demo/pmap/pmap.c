/*
 * Imported from the operating systems class.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/wait.h>

#include "../utils/utils.h"

#define NUM_PAGES 4

static void wait_for_input(const char *msg)
{
	char buf[32];

	printf(" * %s\n", msg);
	printf(" -- Continuing --\n"); fflush(stdout);
	sleep(1);
}

int main(void)
{
	int rc;
	int page_size = getpagesize();
	char *p;
	int fd;

	wait_for_input("before mmap file use pmap to see file mapping");

	/** First we map a file */
	fd = open("Makefile", O_RDWR);
	DIE(fd == -1, "open");

	p = mmap(NULL, page_size,
			PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
	DIE(p == MAP_FAILED, "mmap");
	wait_for_input("after mapping the file");

	rc = munmap(p, page_size);
	DIE(rc == -1, "munmap");
	wait_for_input("after unmapping the file");

	rc = close(fd);
	DIE(rc == -1, "close");

	/** Second we map SHARED memory */
	p = mmap(NULL, page_size, PROT_READ | PROT_WRITE,
				MAP_ANONYMOUS | MAP_SHARED, -1, 0);
	DIE(p == MAP_FAILED, "mmap");
	wait_for_input("after mapping SHARED memory");

	rc = munmap(p, page_size);
	DIE(rc == -1, "munmap");
	wait_for_input("after unmapping SHARED memory");

	/** Thrid we map PRIVATE memory */
	p = mmap(NULL, page_size, PROT_READ | PROT_WRITE,
				MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	DIE(p == MAP_FAILED, "mmap");
	wait_for_input("after mapping PRIVATE memory");

	rc = munmap(p, page_size);
	DIE(rc == -1, "munmap");
	wait_for_input("after unmapping PRIVATE memory");

	return 0;
}
