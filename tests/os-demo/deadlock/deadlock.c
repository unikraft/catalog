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

#define NUM_THREADS		12

static size_t x;
static size_t y;
static pthread_mutex_t xmutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t ymutex = PTHREAD_MUTEX_INITIALIZER;

static void *xfirst(void *arg)
{
	size_t idx = (size_t)arg;
	size_t i;

	printf("xthread %zd running\n", idx);
	pthread_mutex_lock(&xmutex);
	for (i = 0; i < 100000; i++)
		x++;
	pthread_mutex_lock(&ymutex);
	for (i = 0; i < 100000; i++)
		y++;
	pthread_mutex_unlock(&ymutex);
	pthread_mutex_unlock(&xmutex);

	return NULL;
}

static void *yfirst(void *arg)
{
	size_t idx = (size_t)arg;
	size_t i;

	printf("ythread %zd running\n", idx);
	pthread_mutex_lock(&ymutex);
	for (i = 0; i < 100000; i++)
		y++;
	pthread_mutex_lock(&xmutex);
	for (i = 0; i < 100000; i++)
		x++;
	pthread_mutex_unlock(&xmutex);
	pthread_mutex_unlock(&ymutex);

	return NULL;
}

int main(void)
{
	pthread_t threads[2 * NUM_THREADS];
	size_t i;
	int rc;

	for (i = 0; i < NUM_THREADS; i++) {
		rc = pthread_create(&threads[2*i], NULL, xfirst, (void *)i);
		DIE(rc == -1, "pthread_create");
		rc = pthread_create(&threads[2*i+1], NULL, yfirst, (void *)i);
		DIE(rc == -1, "pthread_create");
	}

	for (i = 0; i < 2 * NUM_THREADS; i++) {
		rc = pthread_join(threads[i], NULL);
		DIE(rc == -1, "pthread_join");
	}

	return 0;
}
