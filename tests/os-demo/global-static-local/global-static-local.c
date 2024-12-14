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

static unsigned int age = 33;

static void *thread_func(void *arg)
{
	static unsigned int money = 1000;
	unsigned int books = 10;

	printf("before: age: %u, money: %u, books: %u\n", age, money, books);
	printf("addresses: age: %p, money: %p, books: %p\n", &age, &money, &books);
	age += 2;
	money += 100;
	books += 1;
	printf("after: age: %u, money: %u, books: %u\n", age, money, books);

	return NULL;
}

int main(void)
{
	pthread_t th1, th2;
	int rc;

	rc = pthread_create(&th1, NULL, &thread_func, NULL);
	DIE(rc != 0, "pthread_create");
	rc = pthread_create(&th2, NULL, &thread_func, NULL);
	DIE(rc != 0, "pthread_create");

	rc = pthread_join(th1, NULL);
	DIE(rc != 0, "pthread_join");
	rc = pthread_join(th2, NULL);
	DIE(rc != 0, "pthread_join");

	return 0;
}
