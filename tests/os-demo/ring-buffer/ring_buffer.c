/*
 * Imported from the operating systems class.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "./ring_buffer.h"
#include "../utils/utils.h"

#define is_full(rbuf)				\
	((rbuf)->count == (rbuf)->capacity)

#define is_empty(rbuf)				\
	((rbuf)->count == 0)

#define ring_inc(v, size)			\
	do {					\
		(v) = ((v) + 1) % (size);	\
	} while (0)

int rbuf_init(struct rbuf *rbuf, size_t num_items, size_t item_size)
{
	rbuf->buffer = malloc(num_items * item_size);
	if (rbuf->buffer == NULL)
		return -1;
	rbuf->read_index = 0;
	rbuf->write_index = 0;
	rbuf->item_size = item_size;
	rbuf->capacity = num_items;
	rbuf->count = 0;

	pthread_mutex_init(&rbuf->mutex, NULL);
	pthread_cond_init(&rbuf->empty, NULL);
	pthread_cond_init(&rbuf->full, NULL);

	return 0;
}

void rbuf_destroy(struct rbuf *rbuf)
{
	free(rbuf->buffer);
	pthread_mutex_destroy(&rbuf->mutex);
	pthread_cond_destroy(&rbuf->empty);
	pthread_cond_destroy(&rbuf->full);
}

void rbuf_get(struct rbuf *rbuf, void *item)
{
	pthread_mutex_lock(&rbuf->mutex);
	while (is_empty(rbuf)) {
		puts("Found buffer empty. Waiting.");
		pthread_cond_wait(&rbuf->empty, &rbuf->mutex);
		puts("Buffer has items. Waking up.");
	}
	memcpy(item, rbuf->buffer + rbuf->read_index * rbuf->item_size,
													rbuf->item_size);
	rbuf->count--;
	ring_inc(rbuf->read_index, rbuf->capacity);
	pthread_cond_signal(&rbuf->full);
	pthread_mutex_unlock(&rbuf->mutex);
}

void rbuf_put(struct rbuf *rbuf, void *item)
{
	pthread_mutex_lock(&rbuf->mutex);
	while (is_full(rbuf)) {
		puts("Found buffer full. Waiting.");
		pthread_cond_wait(&rbuf->full, &rbuf->mutex);
		puts("Buffer has room. Waking up.");
	}
	memcpy(rbuf->buffer + rbuf->write_index * rbuf->item_size, item,
													rbuf->item_size);
	rbuf->count++;
	ring_inc(rbuf->write_index, rbuf->capacity);
	pthread_cond_signal(&rbuf->empty);
	pthread_mutex_unlock(&rbuf->mutex);
}
