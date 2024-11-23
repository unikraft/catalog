#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>

#include "utils.h"

#define NUM_THREADS	10

pthread_barrier_t barrier;

int main(void)
{
	int rc;

	rc = pthread_barrier_init(&barrier, NULL, NUM_THREADS);
	DIE(rc < 0, "pthread_barrier_init");

	rc = pthread_barrier_wait(&barrier);
	DIE(rc < 0, "pthread_barrier_wait");

	return 0;
}
