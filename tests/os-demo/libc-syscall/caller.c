/*
 * Imported from the operating systems class.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	char buffer[128];
	FILE *f;

	puts("Hello, World!");
	malloc(100);
	strncpy(buffer, argv[0], strlen(argv[0]));

	f = fopen("a.txt", "w+");
	fclose(f);
	f = fopen("b.txt", "w+");

	write(1, "aaaa\n", 5);

	return 42;
}
