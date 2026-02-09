#include <omp.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

const int N_VALUES = 10e7;
const int N_RUNS = 10;

clock_t start_time;

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
 * Calculate the time in seconds from the start of the application.
 */
double get_time()
{
  clock_t time_diff;
  double time;

  time_diff = clock() - start_time;
  time = (double)(time_diff) / CLOCKS_PER_SEC;

  return time;
}

// Run the aggregation sequentially.
void run_sequential(double* values)
{
  double s;
  double elapsed_time;
  int i, k;

  for (k = 0; k < N_RUNS; ++k) {
    start_time = clock();
    s = 0.0;
    for (i = 0; i < N_VALUES; ++i) {
      s += values[i];
    }
    elapsed_time = get_time();
    // printf(":: Sum = %lf\n", s);
    printf(":: Elapsed time: %lf\n", elapsed_time);
  }
}

// Run the aggregation parallel.
void run_parallel(double* values)
{
  double s;
  double elapsed_time;
  int i, k;

  for (k = 0; k < N_RUNS; ++k) {
    start_time = clock();
    s = 0.0;
    #pragma omp parallel for reduction (+:s)
    for (i = 0; i < N_VALUES; ++i) {
      s += values[i];
    }
    elapsed_time = get_time();
    // printf(":: Sum = %lf\n", s);
    printf(":: Elapsed time: %lf\n", elapsed_time);
  }
}

/**
 * Reduction
 */
int main(int argc, char* argv[])
{
  int thread_id;
  double* values;
  double s;
  int i;

  srand(1234);
  printf("Generate random data ...\n");
  values = generate_data(N_VALUES);

  printf("Sequential runs ...\n");
  run_sequential(values);

  printf("Parallel runs ...\n");
  run_parallel(values);

  free(values);

  return 0;
}

// #pragma omp single
