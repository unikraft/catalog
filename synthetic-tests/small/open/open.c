#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
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
	int rc;
	struct stat statbuf;

	rc = stat("/copy.sql", &statbuf);
	DIE(rc < 0, "stat");

	printf("ino: %lu, nlink: %lu, size: %lu\n", statbuf.st_ino,
			statbuf.st_nlink, statbuf.st_size);

	rc = open("copy.sql", O_RDONLY);
	DIE(rc < 0, "stat");

	return 0;
}
