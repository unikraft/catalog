/*
 * Imported from the operating systems class.
 */

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>

#include "../utils/utils.h"

#define NUM_ROUNDS		1
#define NUM_THREADS		1

static void *show(void *arg)
{
	printf("This is thread %lu\n", pthread_self());

	return NULL;
}

int main(void)
{
	pthread_t ths[NUM_THREADS];
	size_t i, j;

	for (i = 0; i < NUM_ROUNDS; i++) {
		for (j = 0; j < NUM_THREADS; j++)
			DIE(pthread_create(&ths[j], NULL, &show, NULL) != 0,
												"pthread_create");

		for (j = 0; j < NUM_THREADS; j++)
			DIE(pthread_join(ths[j], NULL), "pthread_join");
	}

	return 0;
}
