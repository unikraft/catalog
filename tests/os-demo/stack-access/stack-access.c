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

static unsigned int *stack_var_pointer;

static void *writer(void *arg)
{
	struct timespec ts;

	printf("writer: going to sleep for 2 seconds ...\n");
	ts.tv_sec = 2;
	ts.tv_nsec = 0;
	nanosleep(&ts, NULL);

	printf("writer: write 0x22222222 to reader local_var (address is %p)\n",
															stack_var_pointer);
	*stack_var_pointer = 0x22222222;

	printf("writer: end execution\n");
	return NULL;
}

static void *reader(void *arg)
{
	unsigned int local_var = 0x11111111;
	struct timespec ts;

	stack_var_pointer = &local_var;

	printf("reader: local_var is 0x%08x, local_var address is: %p\n",
		   local_var, &local_var);

	printf("reader: going to for 5 seconds ...\n");
	ts.tv_sec = 5;
	ts.tv_nsec = 0;
	nanosleep(&ts, NULL);

	printf("reader: local_var is 0x%08x\n", local_var);

	printf("reader: end execution\n");
	return NULL;
}

int main(void)
{
	pthread_t th_reader, th_writer;
	int rc;

	rc = pthread_create(&th_reader, NULL, &reader, NULL);
	DIE(rc != 0, "pthread_create");
	rc = pthread_create(&th_writer, NULL, &writer, NULL);
	DIE(rc != 0, "pthread_create");

	rc = pthread_join(th_writer, NULL);
	DIE(rc != 0, "pthread_join");
	rc = pthread_join(th_reader, NULL);
	DIE(rc != 0, "pthread_join");

	return 0;
}
