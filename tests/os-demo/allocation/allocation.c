/*
 * Imported from the operating systems class.
 */

#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include "../utils/utils.h"

#define NUM_ROUNDS		10

static void wait_for_input(const char *msg)
{
	char buf[32];

	printf(" * %s\n", msg);
	printf(" -- Continuing ...\n"); fflush(stdout);
	sleep(1);
}

int main(void)
{
	char *p;
	size_t cnt, i;

	puts("Initializing.");

	for (cnt = 0; cnt < NUM_ROUNDS; cnt++) {
		wait_for_input("Using malloc to allocate 1024 sets of 1024 bytes.");
		p = malloc(1024*1024);
		DIE(p == NULL, "malloc");
		/*for (i = 0; i < 1024; i++) {
			p = malloc(1024);
			DIE(p == NULL, "malloc");
		}*/
	}

	for (cnt = 0; cnt < NUM_ROUNDS; cnt++) {
		wait_for_input("Using mmap to allocate 1MB.");
		p = mmap(NULL, 1024*1024, PROT_READ | PROT_WRITE,
						MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
		DIE(p == MAP_FAILED, "mmap");
	}

	return 0;
}
