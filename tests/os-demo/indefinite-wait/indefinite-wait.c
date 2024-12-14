/**
  * Imported from the operating systems class.
  * 
  * Time of check to time of use race condition
  */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>
#include <time.h>

#include "../utils/utils.h"

#define NUM_PRODUCERS		12
#define NUM_CONSUMERS		12

#define NO_ITEM			0
#define ITEM			42
#define MAX_ITEMS		10

static struct {
	unsigned char storage[MAX_ITEMS];
	size_t size;
} pc_buffer;

static pthread_mutex_t pc_mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t buffer_full_cond = PTHREAD_COND_INITIALIZER;
static pthread_cond_t buffer_empty_cond = PTHREAD_COND_INITIALIZER;

static void *produce(void *arg)
{
	size_t idx = (size_t)arg;

	pthread_mutex_lock(&pc_mutex);
	if (pc_buffer.size >= MAX_ITEMS)
		pthread_cond_wait(&buffer_full_cond, &pc_mutex);
	pc_buffer.storage[pc_buffer.size] = ITEM;
	pc_buffer.size++;
	printf("Producer %zu created item.\n", idx);
	pthread_mutex_unlock(&pc_mutex);

	return NULL;
}

static void *consume(void *arg)
{
	size_t idx = (size_t)arg;

	pthread_mutex_lock(&pc_mutex);
	if (pc_buffer.size == 0)
		pthread_cond_wait(&buffer_empty_cond, &pc_mutex);
	pc_buffer.storage[pc_buffer.size] = NO_ITEM;
	pc_buffer.size--;
	printf("Consumer %zu removed item.\n", idx);
	pthread_mutex_unlock(&pc_mutex);

	return NULL;
}

int main(void)
{
	pthread_t p_threads[NUM_PRODUCERS];
	pthread_t c_threads[NUM_CONSUMERS];
	size_t i;
	int rc;

	for (i = 0; i < NUM_PRODUCERS; i++) {
		rc = pthread_create(&p_threads[i], NULL, produce, (void *)i);
		DIE(rc == -1, "pthread_create");
	}
	printf("Created %d producers.\n", NUM_PRODUCERS);
	puts("Each producer creates one item.");

	for (i = 0; i < NUM_CONSUMERS; i++) {
		rc = pthread_create(&c_threads[i], NULL, consume, (void *)i);
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

	return 0;
}
