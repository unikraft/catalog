/*
 * Imported from the operating systems class.
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>

#include "../utils/utils.h"

#define NUM_THREADS	   2
#define NUM_ROUNDS		10000000


#ifdef USE_SPINLOCK
	pthread_spinlock_t lock;
#else
	pthread_mutex_t lock;
#endif

pthread_barrier_t barrier;
static int shared = 0;


static inline void acquire_lock()
{
#ifdef USE_SPINLOCK
		pthread_spin_lock(&lock);
#else
		pthread_mutex_lock(&lock);
#endif
}

static inline void release_lock()
{
#ifdef USE_SPINLOCK
		pthread_spin_unlock(&lock);
#else
		pthread_mutex_unlock(&lock);
#endif
}

void *thread_func(void *arg)
{
	size_t i;

	pthread_barrier_wait(&barrier);

	for (i = 0; i < NUM_ROUNDS; i++) {
		acquire_lock();
		shared++;
		release_lock();
	}
	return NULL;
}

int main(void)
{
	pthread_t threads[NUM_THREADS];
	size_t i;
	int rc;

#ifdef USE_SPINLOCK
	pthread_spin_init(&lock, PTHREAD_PROCESS_SHARED);
#else
	pthread_mutex_init(&lock, NULL);
#endif
	pthread_barrier_init(&barrier, NULL, NUM_THREADS);

	for (i = 0; i < NUM_THREADS; i++) {
		rc = pthread_create(&threads[i], NULL, thread_func, &i);
		DIE(rc == -1, "pthread_create");
	}

	for (i = 0; i < NUM_THREADS; i++) {
		rc = pthread_join(threads[i], NULL);
		DIE(rc == -1, "pthread_join");
	}

#ifdef USE_SPINLOCK
	printf("Spinlock version - shared = %d\n", shared);
	pthread_spin_destroy(&lock);
#else
	printf("Mutex version - shared = %d\n", shared);
	pthread_mutex_destroy(&lock);
#endif
	pthread_barrier_destroy(&barrier);

	return 0;
}
