/*
 * Imported from the operating systems class.
 */

#include <stdio.h>
#include <stdlib.h>

#include "../utils/utils.h"

int main(void)
{
	FILE *f;

	f = fopen("aaa", "r");
	fclose(f);

	f = fopen("aaa", "w");
	DIE(f == NULL, "fopen");
	fclose(f);

	f = fopen("aaa", "a");
	DIE(f == NULL, "fopen");
	fclose(f);

	f = fopen("aaa", "rw");
	DIE(f == NULL, "fopen");
	fclose(f);

	f = fopen("aaa", "r+");
	DIE(f == NULL, "fopen");
	fclose(f);

	f = fopen("aaa", "w+");
	DIE(f == NULL, "fopen");
	fclose(f);

	f = fopen("aaa", "a+");
	DIE(f == NULL, "fopen");
	fclose(f);

	return 0;
}
