/*
 * Imported from the operating systems class.
 */

#ifndef TESTS_OS_DEMO_RING_BUFFER_RING_BUFFER_H_
#define TESTS_OS_DEMO_RING_BUFFER_RING_BUFFER_H_	  1

#include <pthread.h>

/* ring buffer structure*/
struct rbuf {
	void *buffer;		/* buffer storing items */
	size_t read_index;
	size_t write_index;
	size_t capacity;	 /* maximum number of items */
	size_t count;		/* number of items in buffer */
	size_t item_size;
	pthread_mutex_t mutex;
	pthread_cond_t empty;
	pthread_cond_t full;
};

/* ring buffer functions */
int rbuf_init(struct rbuf *rbuf, size_t num_items, size_t item_size);
void rbuf_destroy(struct rbuf *rbuf);
void rbuf_get(struct rbuf *rbuf, void *item);
void rbuf_put(struct rbuf *rbuf, void *item);

#endif  // TESTS_OS_DEMO_RING_BUFFER_RING_BUFFER_H_
