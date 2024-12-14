/*
 * Imported from the operating systems class.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
		size_t page_size;
	size_t phys_pages;

	page_size = sysconf(_SC_PAGE_SIZE);
	phys_pages = sysconf(_SC_PHYS_PAGES);
	printf("page size: %lu, physical pages: %lu, memory: %lu\n",
			page_size, phys_pages, page_size * phys_pages);

	printf("data cache L1 size: %lu, instruction cache L1 size: %lu\n",
			(size_t)sysconf(_SC_LEVEL1_ICACHE_SIZE),
			(size_t)sysconf(_SC_LEVEL1_DCACHE_SIZE));

	return 0;
}
