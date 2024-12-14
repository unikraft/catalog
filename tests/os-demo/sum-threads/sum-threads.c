/*
 * Imported from the operating systems class.
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

#include "../utils/utils.h"

#ifdef USE_ATOMIC
#define do_op(sum, v)	\
	do {		\
		__sync_fetch_and_add(&(sum), (v)); \
	} while (0)
#else
#define do_op(sum, v)	\
	do {		\
		sum = ((sum) + (v)); \
	} while (0)
#endif

#define NUM_ROUNDS	100000
#define NUM_THREADS   10

#ifdef USE_LONGLONG
static int_64_t sum = 0;
#else
static int64_t sum = 0;
#endif

static void *thread_func(void *arg)
{
	size_t v = (size_t)arg;
	size_t i;

	for (i = 0; i < NUM_ROUNDS; i++)
		do_op(sum, v);

	return NULL;
}

int main(void)
{
	size_t i;
	pthread_t th[NUM_THREADS];
	int rc;

	for (i = 0; i < NUM_THREADS; i++) {
		rc = pthread_create(&th[i], NULL, thread_func, (void *)i);
		DIE(rc < 0, "pthread_create");
	}

	for (i = 0; i < NUM_THREADS; i++) {
		rc = pthread_join(th[i], NULL);
		DIE(rc < 0, "pthread_join");
	}

#ifdef USE_LONGLONG
	printf("sum is: %llu\n", sum);
#else
	printf("sum is: %lu\n", sum);
#endif

	return 0;
}
