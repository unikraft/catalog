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

#define NUM_ROUNDS		1000
#define NUM_THREADS		30

#ifdef USE_REENTRANT
static void *print_time(void *arg)
{
	time_t t = time(NULL);
	size_t i;
	char str_time[NUM_ROUNDS][128];

	for (i = 0; i < NUM_ROUNDS; i++)
		ctime_r(&t, str_time[i]);

	for (i = 0; i < NUM_ROUNDS; i++)
		printf("Thread %zd computed time %s\n", (size_t)arg, str_time[i]);

	return NULL;
}
#else
static void *print_time(void *arg)
{
	time_t t = time(NULL);
	size_t i;
	char *str_time[NUM_ROUNDS];

	for (i = 0; i < NUM_ROUNDS; i++)
		str_time[i] = ctime(&t);

	for (i = 0; i < NUM_ROUNDS; i++)
		printf("Thread %zd computed time %s", (size_t)arg, str_time[i]);

	return NULL;
}
#endif

int main(void)
{
	pthread_t ths[NUM_THREADS];
	size_t i;

	for (i = 0; i < NUM_THREADS; i++)
		DIE(pthread_create(&ths[i], NULL, &print_time,
					(void *)(i + 1)) != 0, "pthread_create");

	for (i = 0; i < NUM_THREADS; i++)
		DIE(pthread_join(ths[i], NULL), "pthread_join");

	return 0;
}
