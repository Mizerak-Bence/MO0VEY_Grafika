#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int N_MAX_THREADS = 4;

pthread_mutex_t thread_count_mutex = PTHREAD_MUTEX_INITIALIZER;
int thread_count = 1;

/**
 * Description of a task for a thread.
 */
typedef struct Task
{
  double* data;
  unsigned long a;
  unsigned long b;
  double result;
} Task;

/**
 * Generate the data for experimentation.
 */
double* generate_data(unsigned long size)
{
  double* data;
  int i;

  data = (double*)malloc(size * sizeof(double));
  for (i = 0; i < size; ++i) {
    data[i] = (double)(rand()) / RAND_MAX;
  }

  return data;
}

/**
 * Aggregate the values recursively on the interval [a, b].
 */
void aggregate_values(Task* task)
{
  int center;
  Task task_1;
  Task task_2;
  pthread_t thread;

  printf("[%d, %d]\n", task->a, task->b);

  if (task->a == task->b) {
    task->result = task->data[task->a];
  } else {
    center = (task->a + task->b) / 2;
    task_1.data = task->data;
    task_1.a = task->a;
    task_1.b = center;
    task_2.data = task->data;
    task_2.a = center + 1;
    task_2.b = task->b;
    pthread_mutex_lock(&thread_count_mutex);
    if (thread_count < N_MAX_THREADS) {
      printf("Start thread ...\n");
      pthread_create(&thread, NULL, aggregate_values, &task_1);
      ++thread_count;
      pthread_mutex_unlock(&thread_count_mutex);
      aggregate_values(&task_2);
      pthread_join(thread, NULL);
      printf("Stop thread ...\n");
      pthread_mutex_lock(&thread_count_mutex);
      --thread_count;
      pthread_mutex_unlock(&thread_count_mutex);
    } else {
      pthread_mutex_unlock(&thread_count_mutex);
      aggregate_values(&task_1);
      aggregate_values(&task_2);
    }
    task->result = task_1.result + task_2.result;
  }
}

/**
 * Main
 */
int main(int argc, char* argv[])
{
  unsigned long size;
  Task task;
  int i;

  size = 1000;
  task.data = generate_data(size);
  for (i = 0; i < size; ++i) {
    printf(":: data[%d] = %lf\n", i, task.data[i]);
  }
  task.a = 0;
  task.b = size - 1;
  aggregate_values(&task);
  printf(":: Result = %lf\n", task.result);
  free(task.data);
}
