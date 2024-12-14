/*
 * Imported from the operating systems class.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

#include "../utils/utils.h"

#define NUM_THREADS		5


static void msg_and_wait(const char *msg)
{
	struct timespec ts;
	char buf[256];

	puts(msg);

	ts.tv_sec = 2;
	ts.tv_nsec = 0;
	nanosleep(&ts, NULL);
}

static void *show(void *arg)
{
	printf("This is thread %lu\n", pthread_self());

	return NULL;
}

int main(void)
{
	pthread_t ths[NUM_THREADS];
	size_t i;

	msg_and_wait("Program started.");

	for (i = 0; i < NUM_THREADS; i++) {
		DIE(pthread_create(&ths[i], NULL, &show, NULL) != 0, "pthread_create");
		msg_and_wait("Created new thread.");
	}

	for (i = 0; i < NUM_THREADS; i++)
		DIE(pthread_join(ths[i], NULL), "pthread_join");

	msg_and_wait("All new threads joined.");

	return 0;
}
