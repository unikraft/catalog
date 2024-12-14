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
#define my_lock()   atomic_lock()
#define my_unlock() atomic_unlock()
#elif USE_SPINLOCK
#define my_lock()   spin_lock()
#define my_unlock() spin_unlock()
#else
#define my_lock()   simple_lock()
#define my_unlock() simple_unlock()
#endif

static unsigned int glock = 0;

static void atomic_lock(void)
{
	while (__sync_bool_compare_and_swap(&glock, 0, 1) == 0) {}
}

static void atomic_unlock(void)
{
	glock = 0;
}

static pthread_spinlock_t spin;

static void spin_lock(void)
{
	pthread_spin_lock(&spin);
}

static void spin_unlock(void)
{
	pthread_spin_unlock(&spin);
}

static void simple_lock(void)
{
	while (glock != 0) {}
	glock = 1;
}

static void simple_unlock(void)
{
	glock = 0;
}

#define NUM_ROUNDS	100000
#define NUM_THREADS	10

static int64_t sum = 0;

static void *thread_func(void *arg)
{
	size_t v = (size_t)arg;
	size_t i;

	for (i = 0; i < NUM_ROUNDS; i++) {
		my_lock();
		sum += v;
		my_unlock();
	}

	return NULL;
}

int main(void)
{
	size_t i;
	pthread_t th[NUM_THREADS];
	int rc;

	pthread_spin_init(&spin, 0);

	for (i = 0; i < NUM_THREADS; i++) {
		rc = pthread_create(&th[i], NULL, thread_func, (void *)i);
		DIE(rc < 0, "pthread_create");
	}

	for (i = 0; i < NUM_THREADS; i++) {
		rc = pthread_join(th[i], NULL);
		DIE(rc < 0, "pthread_join");
	}

	pthread_spin_destroy(&spin);

	printf("sum is: %lu\n", sum);

	sleep(2);
	return 0;
}
