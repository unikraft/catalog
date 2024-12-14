/*
 * Imported from the operating systems class.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

static void wait_for_input(const char *msg)
{
	char buf[32];

	printf(" * %s\n", msg);
	printf(" -- Continuing ...\n");
	fflush(stdout);
	sleep(1);
}

int main(int argc, char **argv)
{
	size_t bytes;
	char *ptr;

	if (argc != 2) {
		fprintf(stderr, "Usage: $0 allocation-size\n\n");
		exit(EXIT_FAILURE);
	}

	wait_for_input("before malloc()");
	bytes = strtol(argv[1], NULL, 10);
	printf("Allocating %zu bytes\n", bytes);
	ptr = malloc(bytes);
	ptr = malloc(bytes);

	wait_for_input("before free()");
	printf("Freeing %zu bytes\n", bytes);
	free(ptr);

	wait_for_input("before end of program");

	return 0;
}
