/*
 * Imported from the operating systems class.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>

#include "../utils/utils.h"

static void wait_for_input(const char *msg)
{
	char buf[32];

	printf(" * %s\n", msg);
	printf(" -- Continuing ...\n"); fflush(stdout);
	sleep(1);
}

static void stack_allocation(void)
{
	wait_for_input("before stack allocation");
	printf("Allocate 16 pages of stack memory.\n");
	{
		char buffer[65536];	/* 16 pages of stack memory */
	}

	wait_for_input("before stack free");
	printf("Free 16 pages of stack memory.\n");
	/* When returning stack is automatically discarded. */
}

static void heap_allocation(void)
{
	char *ptr;

	wait_for_input("before heap allocation");
	printf("Allocate 16 pages of heap memory.\n");
	ptr = malloc(65536);

	wait_for_input("before heap free");
	printf("Free 16 pages of heap memory.\n");
	free(ptr);
}

static void mapped_allocation(void)
{
	char *ptr;

	wait_for_input("before mapped allocation");
	printf("Allocate 16 pages of mapped memory.\n");
	ptr = mmap(NULL, 65536, PROT_READ | PROT_WRITE,
				MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	DIE(ptr == MAP_FAILED, "mmap");

	wait_for_input("before mapped free");
	printf("Free 16 pages of mpped memory.\n");
	munmap(ptr, 65536);
}

int main(void)
{
	/* Stack-based memory allocation and deallocation */
	stack_allocation();

	/* Heap-based memory allocation and deallocation */
	heap_allocation();

	/* Memory mapping-based allocation and deallocation */
	mapped_allocation();

	return 0;
}
