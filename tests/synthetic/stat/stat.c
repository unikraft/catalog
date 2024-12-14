#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>

/* error printing macro */
#define ERR(call_description)								\
	do {													\
		fprintf(stderr, "(%s, %d): %s: %s (errno: %d)\n", \
				__FILE__, __LINE__,			\
				call_description,				\
				strerror(errno),				\
				errno);						\
	} while (0)

/* print error (call ERR) and exit */
#define DIE(assertion, call_description)			\
	do {											\
		if (assertion) {						\
			ERR(call_description);		\
			exit(EXIT_FAILURE);			\
		}									\
	} while (0)


/* print field of stat structure */
#define print_stat_field_value(field, value)				\
	printf(" * %-12s value: %10lu, size: %2lu, offset: %2lu\n",	\
			#field ":", (int64_t) value,		\
			sizeof(statbuf.field),				\
			offsetof(struct stat, field))

#define print_stat_field(field)						\
	print_stat_field_value(field, statbuf.field);

int main(void)
{
	int rc;

	struct stat statbuf;

	rc = stat("/file", &statbuf);
	DIE(rc < 0, "stat");

	print_stat_field(st_dev);
	print_stat_field(st_ino);
	print_stat_field(st_mode);
	print_stat_field(st_nlink);
	print_stat_field(st_uid);
	print_stat_field(st_gid);
	print_stat_field(st_rdev);
	print_stat_field(st_size);
	print_stat_field(st_blksize);
	print_stat_field(st_blocks);
	print_stat_field_value(st_atim, 0);
	print_stat_field_value(st_mtim, 0);
	print_stat_field_value(st_ctim, 0);

	printf("\ntotal size: %lu\n", sizeof(statbuf));

	return 0;
}
