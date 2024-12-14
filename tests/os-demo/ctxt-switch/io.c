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
	size_t i, j;
	size_t val = 0x12345678;

	for (i = 0; i < 10; i++) {
		val = val ^ i;
		for (j = 0; j < 10; j++)
			write(STDOUT_FILENO, "a", 1);
		sleep(1);
	}

	return 0;
}
