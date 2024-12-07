#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>

/* error printing macro */
#define ERR(call_description)                                     \
	do {                                                      \
		fprintf(stderr, "(%s, %d): %s: %s (errno: %d)\n", \
				__FILE__, __LINE__,               \
				call_description,                 \
				strerror(errno),                  \
				errno);                           \
	} while (0)

/* print error (call ERR) and exit */
#define DIE(assertion, call_description)                \
	do {                                            \
		if (assertion) {                        \
			ERR(call_description);          \
			exit(EXIT_FAILURE);             \
		}                                       \
	} while(0)


int main(void)
{
	int s;

	s = socket(PF_INET, SOCK_STREAM, 0);
	DIE(s < 0, "socket");

	return 0;
}
