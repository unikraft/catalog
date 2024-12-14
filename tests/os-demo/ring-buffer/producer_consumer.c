/*
 * Imported from the operating systems class.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

#include "./ring_buffer.h"
#include "../utils/utils.h"

#define NUM_ROUNDS	   10
#define NUM_CONSUMERS	10
#define NUM_PRODUCERS	10

/* globally accessible ring buffer */
static struct rbuf rbuf;

static void *consume(void *arg)
{
	size_t idx = (size_t)arg;
	size_t i;
	size_t v;

	for (i = 0; i < NUM_ROUNDS; i++) {
		rbuf_get(&rbuf, &v);
		printf("Consumer %zu consumed item %zu\n", idx, v);
	}

	return NULL;
}

static void *produce(void *arg)
{
	size_t idx = (ssize_t)arg;
	size_t i;
	size_t v = idx;

	for (i = 0; i < NUM_ROUNDS; i++) {
		rbuf_put(&rbuf, &v);
		printf("Producer %zu produced item %zu\n", idx, v);
	}

	return NULL;
}

int main(void)
{
	size_t i;
	pthread_t cth[NUM_CONSUMERS];
	pthread_t pth[NUM_PRODUCERS];
	int rc;

	/* Create ring buffer with capacity for 10 integers. */
	rc = rbuf_init(&rbuf, 10, sizeof(size_t));
	DIE(rc < 0, "rbuf_init");

	for (i = 0; i < NUM_CONSUMERS; i++) {
		rc = pthread_create(&cth[i], NULL,  consume, (void *)i);
		DIE(rc < 0, "pthread_create");
	}
	for (i = 0; i < NUM_PRODUCERS; i++) {
		rc = pthread_create(&pth[i], NULL, produce, (void *)i);
		DIE(rc < 0, "pthread_create");
	}

	for (i = 0; i < NUM_CONSUMERS; i++) {
		rc = pthread_join(cth[i], NULL);
		DIE(rc < 0, "pthread_join");
	}
	for (i = 0; i < NUM_PRODUCERS; i++) {
		rc = pthread_join(pth[i], NULL);
		DIE(rc < 0, "pthread_join");
	}

	rbuf_destroy(&rbuf);

	return 0;
}
