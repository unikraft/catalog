/*
 * Imported from the operating systems class.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "../utils/utils.h"

int main(void)
{
	FILE *f;
	size_t i;

	for (i = 0; i < 10; i++) {
		printf("a");
		sleep(1);
	}
	printf("\n");

	f = fopen("f.txt", "w+");
	DIE(f == NULL, "fopen");

	for (i = 0; i < 10; i++) {
		fprintf(f, "a");
		fprintf(f, "\n");
		sleep(1);
	}
	fflush(f);

	fclose(f);

	return 0;
}
