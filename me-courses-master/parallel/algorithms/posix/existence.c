#include <pthread.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

const int BATCH_SIZE = 100;
const int N_THREADS = 4;

pthread_mutex_t batch_mutex = PTHREAD_MUTEX_INITIALIZER;

bool is_existing_value = false;

/**
 * Description of a task for a thread.
 */
typedef struct Task
{
  int value;
  int* data;
  unsigned long size;
  unsigned long start_index;
  unsigned long step;
} Task;

/**
 * Generate the data for experimentation.
 */
int* generate_data(unsigned long size)
{
  int* data;
  int i;

  data = (int*)malloc(size * sizeof(int));
  for (i = 0; i < size; ++i) {
    data[i] = 100 * (double)(rand()) / RAND_MAX;
  }

  return data;
}

/**
 * Find the value.
 */
void find_value(Task* task)
{
  int n_steps;
  int i;

  n_steps = 0;
  for (i = task->start_index; i < task->size; i += task->step) {
    if (task->data[i] == task->value) {
      pthread_mutex_lock(&batch_mutex);
      is_existing_value = true;
      printf("---> Found by %d at %d!\n", task->start_index, i);
      pthread_mutex_unlock(&batch_mutex);
      return;
    }
    ++n_steps;
    if (n_steps == BATCH_SIZE) {
      pthread_mutex_lock(&batch_mutex);
      if (is_existing_value == true) {
        pthread_mutex_unlock(&batch_mutex);
        return;
      }
      pthread_mutex_unlock(&batch_mutex);
      n_steps = 0;
    }
  }
}

/**
 * Main
 */
int main(int argc, char* argv[])
{
  int* data;
  Task tasks[N_THREADS];
  pthread_t threads[N_THREADS];
  int i;
  int size;

  size = 1000;
  data = generate_data(size);
  for (i = 0; i < size; ++i) {
    // printf(":: data[%d] = %d\n", i, data[i]);
  }
  for (i = 0; i < N_THREADS; ++i) {
    tasks[i].data = data;
    tasks[i].size = size;
    tasks[i].start_index = i;
    tasks[i].step = N_THREADS;
    tasks[i].value = 10;
    printf(":: Start thread %d ...\n", i);
    pthread_create(&threads[i], NULL, find_value, tasks + i);
  }
  for (i = 0; i < N_THREADS; ++i) {
    pthread_join(threads[i], NULL);
  }
  printf(":: Result = %d\n", is_existing_value);
  free(data);
}
