/*
 * Imported from the operating systems class.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	int n;

	if (argc < 2) {
		fprintf(stderr, "Usage: %s <argument>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	printf(argv[1]);

	return 0;
}
