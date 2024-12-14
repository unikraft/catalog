/*
 * Imported from the operating systems class.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TEST_STRING	"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"

int main(void)
{
	char a[24];
	memset(a, 0, sizeof(a));

	printf("sizeof(a) = %lu, strlen(TEST_STRING) = %lu\n",
		   sizeof(a), strlen(TEST_STRING));

	memcpy(&a[0], TEST_STRING, strlen(TEST_STRING));

	return 0;
}
