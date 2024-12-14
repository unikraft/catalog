/*
 * Imported from the operating systems class.
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include "../utils/utils.h"

#define NUM_THREADS				30
#define INCREMENTS_PER_THREAD	100000

#define GRANULARITY_COARSE			1
#define GRANULARITY_FINE			2

static size_t value = 0;
static pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

static void *useless_work(void *arg)
{
	size_t i;

#if GRANULARITY_TYPE == GRANULARITY_FINE
	for (i = 0; i < INCREMENTS_PER_THREAD; i++) {
		pthread_mutex_lock(&m);
		value++;
		pthread_mutex_unlock(&m);
	}
#elif GRANULARITY_TYPE == GRANULARITY_COARSE
	pthread_mutex_lock(&m);
	for (i = 0; i < INCREMENTS_PER_THREAD; i++) {
		value++;
	}
	pthread_mutex_unlock(&m);
#endif

	return NULL;
}

int main(void)
{
	pthread_t threads[NUM_THREADS];
	size_t i;
	int rc;

	/* Create threads. */
	for (i = 0; i < NUM_THREADS; i++) {
		rc = pthread_create(&threads[i], NULL, useless_work, NULL);
		DIE(rc != 0, "pthread_create");
	}

	/* Wait for threads, show termination code and close handled. */
	for (i = 0; i < NUM_THREADS; i++) {
		rc = pthread_join(threads[i], NULL);
		DIE(rc != 0, "pthread-join");
	}

	pthread_mutex_destroy(&m);
	return 0;
}
