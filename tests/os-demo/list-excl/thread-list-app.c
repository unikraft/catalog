/*
 * Imported from the operating systems class.
 */

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <time.h>

#include "../utils/utils.h"
#include "./list.h"

#define NUM_THREADS	10
#define NUM_ROUNDS   1000
#define MAX_ITEM	65536

enum list_action {
	ADD_ITEM,
	ADD_ITEM_TAIL,
	INSERT_ITEM,
	REMOVE_ITEM,
	SEARCH_ITEM,
	NO_ACTION
};

/* list head (sentinel) */
static struct int_list *head;

#ifdef USE_MUTEX
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
#endif

/*
 * Each thread does NUM_ROUNDS random actions.
 */

static void *thread_fn(void *arg)
{
	size_t i;
	enum list_action action;
	int item;
	size_t size, pos;

	sleep(1);

	for (i = 0; i < NUM_ROUNDS; i++) {
		/* Create random action. */
		action = rand_r(NULL) % NO_ACTION;

		switch (action) {
		case ADD_ITEM:
			item = rand_r(NULL) % MAX_ITEM;
#ifdef USE_MUTEX
			pthread_mutex_lock(&mutex);
#endif
			list_add_item(head, item);
#ifdef USE_MUTEX
			pthread_mutex_unlock(&mutex);
#endif
			break;
		case ADD_ITEM_TAIL:
			item = rand_r(NULL) % MAX_ITEM;
#ifdef USE_MUTEX
			pthread_mutex_lock(&mutex);
#endif
			list_add_item_tail(head, item);
#ifdef USE_MUTEX
			pthread_mutex_unlock(&mutex);
#endif
			break;
		case INSERT_ITEM:
			item = rand_r(NULL) % MAX_ITEM;
			size = list_get_size(head);
			pos = rand_r(NULL) % size;
#ifdef USE_MUTEX
			pthread_mutex_lock(&mutex);
#endif
			list_insert_item(head, pos, item);
#ifdef USE_MUTEX
			pthread_mutex_unlock(&mutex);
#endif
			break;
		case REMOVE_ITEM:
			size = list_get_size(head);
			pos = rand_r(NULL) % size;
#ifdef USE_MUTEX
			pthread_mutex_lock(&mutex);
#endif
			list_remove_item(head, pos);
#ifdef USE_MUTEX
			pthread_mutex_unlock(&mutex);
#endif
			break;
		case SEARCH_ITEM:
			item = rand_r(NULL) % MAX_ITEM;
#ifdef USE_MUTEX
			pthread_mutex_lock(&mutex);
#endif
			(void) list_search_item(head, item);
#ifdef USE_MUTEX
			pthread_mutex_unlock(&mutex);
#endif
			break;
		default:
			break;
		}
	}

	return NULL;
}

int main(void)
{
	pthread_t th[NUM_THREADS];
	size_t i;
	int item;
	int rc;

#ifdef USE_MUTEX
	printf("With mutex:\n");
#else
	printf("Without mutex:\n");
#endif

	head = malloc(sizeof(*head));
	DIE(head == NULL, "malloc");
	list_init_head(head);

	/* Initialize random seed. */
	srand(time(NULL));

	/* Initialize list to 1024 items. */
	for (i = 0; i < 1024; i++) {
		item = rand_r(NULL);
		list_add_item(head, item);
	}

	for (i = 0; i < NUM_THREADS; i++) {
		rc = pthread_create(th + i, NULL, thread_fn, NULL);
		DIE(rc != 0, "pthread_create");
	}

	for (i = 0; i < NUM_THREADS; i++) {
		rc = pthread_join(th[i], NULL);
		DIE(rc != 0, "pthread_join");
	}

	return 0;
}
