#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int N_THREADS = 16;

/**
 * Description of a task for a thread.
 */
typedef struct Task
{
  double* data;
  unsigned long offset;
  unsigned long length;
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
 * Calculate the elapsed time between the given two time points.
 */
double calc_elapsed_time(struct timespec* start_time, struct timespec* finish_time)
{
  double elapsed_time;

  elapsed_time = (finish_time->tv_sec - start_time->tv_sec);
  elapsed_time += (double)(finish_time->tv_nsec - start_time->tv_nsec) / 1000000000;

  return elapsed_time;
}

/**
 * Map the values.
 */
void map_values(void* param)
{
  Task* task;
  int i;
  int index;
  pid_t tid;

  tid = gettid();
  task = (Task*)param;
  printf("[%d] offset = %lu, length = %lu\n", tid, task->offset, task->length);
  for (i = 0; i < task->length; ++i) {
    index = task->offset + i;
    task->data[index] = sqrt(task->data[index] * 10);
  }
}

/**
 * Main
 */
int main(int argc, char* argv[])
{
  int i, j;
  unsigned long size;
  double* data;
  struct timespec start_time;
  struct timespec finish_time;
  double elapsed_time;
  pthread_t threads[N_THREADS];
  Task tasks[N_THREADS];
  int length;

  for (i = 0; i <= 10; ++i) {
    size = i * 10000000;
    printf(":: size = %lu\n", size);
    data = generate_data(size);
    clock_gettime(CLOCK_MONOTONIC_RAW, &start_time);
    length = size / N_THREADS;
    printf(":: Create threads ...\n");
    for (j = 0; j < N_THREADS; ++j) {
      tasks[j].data = data;
      tasks[j].offset = j * length;
      tasks[j].length = length;
      pthread_create(&threads[j], NULL, map_values, tasks + j);
    }
    printf(":: Join threads ...\n");
    for (j = 0; j < N_THREADS; ++j) {
      pthread_join(threads[j], NULL);
    }
    clock_gettime(CLOCK_MONOTONIC_RAW, &finish_time);
    elapsed_time = calc_elapsed_time(&start_time, &finish_time);
    printf(":: time %lu;%lf\n", size, elapsed_time);
    free(data);
  }

  return 0;
}
