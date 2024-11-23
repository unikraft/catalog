#ifndef LIN_UTILS_H_
#define LIN_UTILS_H_	1

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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

#endif
