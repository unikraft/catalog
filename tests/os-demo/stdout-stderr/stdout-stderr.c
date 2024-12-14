/*
 * Imported from the operating systems class.
 */

#include <stdio.h>
#include <unistd.h>

/*
 * Change to 'stderr' to see when buffer flushing occurs.
 * stderr is unbuffered. Flushing is done at each call.
 * stdout is line buffered. Flushing happens at newline.
 *
 * Check the setvbuf(3) man page for additional info.
 */
#define writer		stderr

static void write_and_sleep(const char *message)
{
	fputs(message, writer);
	sleep(2);
}

int main(void)
{
	write_and_sleep("All");
	write_and_sleep(" your");
	write_and_sleep(" base");
	write_and_sleep(" are");
	write_and_sleep(" belong");
	write_and_sleep(" to");
	write_and_sleep(" us!");

	return 0;
}
