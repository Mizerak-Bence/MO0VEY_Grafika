#include "sudoku.h"
#include "utils.h"

/**
 * Sudoku solver
 */
int main(int argc, char* argv[])
{
  struct timespec start_time;
  struct timespec finish_time;
  double elapsed_time;
  double sequential_avg_time;
  double parallel_avg_time;
  int i;

  // TODO: Load table from file!
  int table[9][9] = {
    {5, 0, 0, 0, 0, 0, 4, 0, 0},
    {0, 0, 2, 0, 0, 1, 0, 3, 0},
    {0, 7, 0, 4, 0, 0, 8, 0, 9},
    {0, 0, 1, 0, 4, 7, 3, 0, 0},
    {0, 8, 7, 0, 0, 3, 6, 0, 4},
    {3, 0, 9, 0, 8, 6, 7, 1, 0},
    {9, 6, 0, 1, 7, 0, 2, 8, 5},
    {0, 1, 0, 3, 0, 0, 0, 0, 6},
    {0, 0, 0, 6, 0, 9, 0, 0, 3}
  };

  sequential_avg_time = 0.0;
  parallel_avg_time = 0.0;
  for (i = 0; i < 1000; ++i) {
    clock_gettime(CLOCK_MONOTONIC_RAW, &start_time);
    solve(table, 0, 0);
    clock_gettime(CLOCK_MONOTONIC_RAW, &finish_time);
    elapsed_time = calc_elapsed_time(&start_time, &finish_time);
    sequential_avg_time += elapsed_time;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start_time);
    solve_in_threads(table, 0, 1);
    clock_gettime(CLOCK_MONOTONIC_RAW, &finish_time);
    elapsed_time = calc_elapsed_time(&start_time, &finish_time);
    parallel_avg_time += elapsed_time;
  }

  // printf(":: time %lf\n", elapsed_time);
  printf("Sequential : %lf seconds\n", sequential_avg_time);
  printf("Parallel   : %lf seconds\n", parallel_avg_time);

  return 0;
}
