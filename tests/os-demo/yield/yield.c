/*
 * Imported from the operating systems class.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>
#include <time.h>

#include "../utils/utils.h"

#define diff_us(ta, tb)		\
	(((ta).tv_sec - (tb).tv_sec) * 1000 * 1000 + \
	 ((ta).tv_nsec - (tb).tv_nsec) / 1000)

int main(void)
{
	size_t round_no, i, j, val = 0x12345678;
	struct timespec time_before, time_after;

	for (round_no = 0; round_no < 10; round_no++) {
		for (i = 0; i < 1000000; i++) {
			val = val ^ i;
			for (j = 0; j < 300; j++)
				val = val ^ j;
		}
		clock_gettime(CLOCK_REALTIME, &time_before);
		sched_yield();
		clock_gettime(CLOCK_REALTIME, &time_after);
		printf("run %zu, time passed %ld microseconds\n",
				round_no, diff_us(time_after, time_before));
	}

	return 0;
}
