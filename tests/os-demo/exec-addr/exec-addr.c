/*
 * Imported from the operating systems class.
 *
 * Show addresses in executable and in process.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../utils/utils.h"

static int exec_static_int_global = 1;
int exec_int_global = 2;
int exec_int_global_noinit;
const char exec_array_ro[] = "hello";

/* Show message and wait for ENTER key press. */
static void msg_and_wait(const char *msg)
{
	char buf[256];

	puts(msg);
	sleep(1);
}

static void simple_func(void)
{
	printf("Inside %s\n\n", __func__);
}

int main(void)
{
	simple_func();

	printf("Run-time addresses are:\n");
	printf("&exec_static_int_global: %p\n", &exec_static_int_global);
	printf("&exec_int_global: %p\n", &exec_int_global);
	printf("&exec_int_global_noinit: %p\n", &exec_int_global_noinit);
	printf("&exec_array_ro: %p\n", &exec_array_ro);
	printf("&simple_func: %p\n", simple_func);
	printf("&main: %p\n", main);

	msg_and_wait("\nRun `pmap -p $(pidof exec-addr)' to show process map.\n");

	return 0;
}
