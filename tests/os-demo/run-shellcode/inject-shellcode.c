/*
 * Imported from the operating systems class.
 */

#include <stdio.h>

static char shellcode[64];

int main(void)
{
	void (*f)(void) = (void (*)(void)) shellcode;

	printf("Give data: ");
	fgets(shellcode, 64, stdin);
	f();

	return 0;
}
