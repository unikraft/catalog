/*
 * Imported from the operating systems class.
 */

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	FILE *f;
	size_t i;

	for (i = 0; i < 1030; i++) {
		printf("i = %zu, open file\n", i);
		f = fopen("aaa", "r");
		if (f == NULL) {
			perror("fopen");
			break;
		}
	}

	printf("Opened %zu file descriptors.\n", i);

	return 0;
}
