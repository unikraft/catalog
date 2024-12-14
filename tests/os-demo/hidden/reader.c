/*
 * Imported from the operating systems class.
 */

#include <stdio.h>
#include <stdlib.h>
#include "./reader.h"

unsigned int read_uint(const char *message)
{
	char buffer[128];

	printf("%s", message);
	fgets(buffer, 128, stdin);

	return strtol(buffer, NULL, 10);
}
