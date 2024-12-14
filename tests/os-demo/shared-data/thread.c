/*
 * Imported from the operating systems class.
 */

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>

#include "../utils/utils.h"

static unsigned int data_var = 0;

static void *inc(void *arg)
{
	data_var++;
	printf("data_var = %d\n", data_var);

	return NULL;
}

int main(void)
{
	pthread_t th;

	DIE(pthread_create(&th, NULL, &inc, NULL) != 0, "pthread_create");

	sleep(2);
	inc(NULL);

	DIE(pthread_join(th, NULL), "pthread_join");

	return 0;
}
