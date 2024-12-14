/*
 * Imported from the operating systems class.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../utils/utils.h"

static void actual_func(void)
{
	printf("Call actual function.\n\n");
}

static void inject_func(void)
{
	printf("Call injected function.\n\n");
	exit(EXIT_SUCCESS);
}

static size_t read_data(void)
{
	void (*func_ptr)(void) = actual_func;
	char buffer[16];

	memset(buffer, 'A', 16);
	printf("Insert message (less than 16 bytes): ");
	fgets(buffer, 48, stdin);
	printf("buffer: %p\n", buffer);
	func_ptr();

	return strlen(buffer);
}

int main(void)
{
	size_t len;

	len = read_data();
	printf("\nRead %zd bytes from standard input.\n", len);

	return 0;
}
