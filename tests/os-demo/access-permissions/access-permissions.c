/*
 * Imported from the operating systems class.
 */

#include <stdio.h>

static int data[] = {10, 20, 30, 40};	/* stored in .data section (rw-) */

static void exec_do_nothing(void) {}	/* stored in .text section (r-x) */

static void do_write(const char *msg, int *address, int value)
{
	puts(msg);
	*address = value;
}

static void do_read(const char *msg, int *address)
{
	int p;

	puts(msg);
	p = *address;
}

static void do_exec(const char *msg, void *address)
{
	void (*f)(void) = (void (*)(void)) address;

	puts(msg);
	f();
}

int main(void)
{
	do_read("reading from .data section", &data[0]);
	do_write("writing to .data section", &data[0], 77);

	do_read("reading from .text section", exec_do_nothing);
	do_exec("executing .text section", exec_do_nothing);

	/* These won't work due to permission issues. */
	// do_exec("executing .data section", &data[0]);
	// do_write("writing to .text section", exec_do_nothing, 77);
	// do_read("reading from NULL", NULL);

	return 0;
}
