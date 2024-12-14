/*
 * Imported from the operating systems class.
 */

#include <stdio.h>
#include <string.h>

char buffer[128];
char secret[] = "p422w0rd";

int main(void)
{
	int n;

	strncpy(buffer, "Hello, World!", 14);
	printf("n = ");
	scanf("%d", &n);

	printf("0x%02hhx (%c)\n", buffer[n * sizeof(int)], buffer[n * sizeof(int)]);

	return 0;
}
