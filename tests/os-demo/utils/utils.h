/*
 * Imported from the operating systems class.
 */

#ifndef TESTS_OS_DEMO_UTILS_UTILS_H_
#define TESTS_OS_DEMO_UTILS_UTILS_H_	1

#include <stdio.h>
#include <stdlib.h>

/* useful macro for handling error codes */
#define DIE(assertion, call_description)			\
	do {								\
		if (assertion) {					\
			fprintf(stderr, "(%s, %d): ",			\
					__FILE__, __LINE__);		\
			perror(call_description);			\
			exit(EXIT_FAILURE);				\
		}							\
	} while (0)

#endif  // TESTS_OS_DEMO_UTILS_UTILS_H_
