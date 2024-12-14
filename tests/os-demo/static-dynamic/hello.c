/*
 * Imported from the operating systems class.
 */

#include <stdio.h>

static void wait_for_input(const char *msg)
{
	char buf[32];

	printf(" * %s\n", msg);
	printf(" -- Continuing ...\n"); fflush(stdout);
}

int main(void)
{
	wait_for_input("Hello, world!");
	return 0;
}
