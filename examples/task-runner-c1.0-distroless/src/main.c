
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define WORKERS 2
#define TASKS 3

typedef enum {
    TASK_ADD,
    TASK_FIB,
    TASK_SQUARE
} task_type_t;

typedef struct {
    task_type_t type;
    int a;
    int b;
} task_t;

static task_t queue[TASKS];
static int queue_size = 0;
static int next_task = 0;

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

static int fibonacci(int n)
{
    if (n <= 1)
        return n;

    return fibonacci(n - 1) + fibonacci(n - 2);
}

static void execute_task(task_t *task, int worker)
{
    int result;

    switch (task->type) {
    case TASK_ADD:
        result = task->a + task->b;
        printf("[worker-%d] ADD(%d, %d) = %d\n",
               worker, task->a, task->b, result);
        break;

    case TASK_FIB:
        result = fibonacci(task->a);
        printf("[worker-%d] FIB(%d) = %d\n",
               worker, task->a, result);
        break;

    case TASK_SQUARE:
        result = task->a * task->a;
        printf("[worker-%d] SQUARE(%d) = %d\n",
               worker, task->a, result);
        break;
    }
}

static void *worker(void *arg)
{
    int worker_id = *(int *)arg;

    while (1) {
        task_t task;

        pthread_mutex_lock(&mutex);

        if (next_task >= queue_size) {
            pthread_mutex_unlock(&mutex);
            break;
        }

        task = queue[next_task++];
        pthread_mutex_unlock(&mutex);

        execute_task(&task, worker_id);
    }

    return NULL;
}

static void submit_task(task_t task)
{
    if (queue_size < TASKS)
        queue[queue_size++] = task;
}

int main(void)
{
    pthread_t threads[WORKERS];
    int worker_ids[WORKERS];

    printf("Task Runner\n");
    printf("===========\n\n");

    submit_task((task_t){TASK_ADD, 10, 32});
    submit_task((task_t){TASK_FIB, 10, 0});
    submit_task((task_t){TASK_SQUARE, 7, 0});

    for (int i = 0; i < WORKERS; i++) {
        worker_ids[i] = i + 1;
        pthread_create(&threads[i], NULL, worker, &worker_ids[i]);
    }

    for (int i = 0; i < WORKERS; i++)
        pthread_join(threads[i], NULL);

    printf("\nCompleted: %d tasks\n", queue_size);

    return 0;
}

