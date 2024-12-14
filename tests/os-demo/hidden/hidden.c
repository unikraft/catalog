/*
 * Imported from the operating systems class.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "./reader.h"

static unsigned int test = 21;
static char success_message[128] = "failed";

static void hidden_function(unsigned int rand)
{
	if (test == rand)
		puts(success_message);
}

int main(void)
{
	unsigned int r1, r2;
	unsigned int in;

	hidden_function(100);

	srand(time(NULL));
	r1 = rand_r(NULL);
	r2 = rand_r(NULL);
	in = read_uint("Give number: ");
	if (in == r1)
		hidden_function(r2);

	return 0;
}
