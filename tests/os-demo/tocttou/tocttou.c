/*
 * Imported from the operating systems class.
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>
#include <time.h>

#include "../utils/utils.h"

#define NUM_PRODUCERS		50
#define NUM_CONSUMERS		10
#define NUM_ITEMS_PRODUCER   1
#define NUM_ITEMS_CONSUMER   5
#define TS_50_MILLISECONDS   {0, 50000000}

static int num_items;

static void *produce(void *arg)
{
	struct timespec ts = TS_50_MILLISECONDS;

	nanosleep(&ts, NULL);
	num_items += NUM_ITEMS_PRODUCER;	/* Produce. */

	return NULL;
}

static void *consume(void *arg)
{
	struct timespec ts = TS_50_MILLISECONDS;

	nanosleep(&ts, NULL);
	if (num_items >= NUM_ITEMS_CONSUMER) {
		nanosleep(&ts, NULL);		/* Do other work. */
		num_items -= NUM_ITEMS_CONSUMER;	/* Consume. */
	}

	return NULL;
}

int main(void)
{
	pthread_t p_threads[NUM_PRODUCERS];
	pthread_t c_threads[NUM_CONSUMERS];
	size_t i;
	int rc;

	for (i = 0; i < NUM_PRODUCERS; i++) {
		rc = pthread_create(&p_threads[i], NULL, produce, NULL);
		DIE(rc == -1, "pthread_create");
	}
	printf("Created %d producers.\n", NUM_PRODUCERS);
	puts("Each producer creates one item.");

	for (i = 0; i < NUM_CONSUMERS; i++) {
		rc = pthread_create(&c_threads[i], NULL, consume, NULL);
		DIE(rc == -1, "pthread_create");
	}
	printf("Created %d consumers.\n", NUM_CONSUMERS);
	puts("Each producer removes one item.");

	for (i = 0; i < NUM_PRODUCERS; i++) {
		rc = pthread_join(p_threads[i], NULL);
		DIE(rc == -1, "pthread_join");
	}

	for (i = 0; i < NUM_CONSUMERS; i++) {
		rc = pthread_join(c_threads[i], NULL);
		DIE(rc == -1, "pthread_join");
	}

	printf("Num items at the end: %d\n", num_items);

	return 0;
}
