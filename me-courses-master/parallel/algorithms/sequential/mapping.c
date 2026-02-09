#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

  for (i = 0; i <= 10; ++i) {
    size = i * 10000000;
    data = generate_data(size);
    clock_gettime(CLOCK_MONOTONIC_RAW, &start_time);
    for (j = 0; j < size; ++j) {
      data[j] = sqrt(data[j] * 10);
    }
    clock_gettime(CLOCK_MONOTONIC_RAW, &finish_time);
    elapsed_time = calc_elapsed_time(&start_time, &finish_time);
    printf("%lu;%lf\n", size, elapsed_time);
    free(data);
  }

  return 0;
}
