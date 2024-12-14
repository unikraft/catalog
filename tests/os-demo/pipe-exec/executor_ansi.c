/*
 * Imported from the operating systems class.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../utils/utils.h"


#ifndef BUFSIZ
#define BUFSIZ	  256
#endif

static char buffer[BUFSIZ];

int main(void)
{
	FILE *read_f, *write_f;

	/* Create child processes with redirection. */
	write_f = popen("./reader", "w");
	DIE(write_f == NULL, "popen");
	read_f = popen("./writer", "r");
	DIE(read_f == NULL, "popen");

	fgets(buffer, BUFSIZ, read_f);
	fputs(buffer, write_f);

	/* Close processes. */
	pclose(read_f);
	pclose(write_f);

	return 0;
}
