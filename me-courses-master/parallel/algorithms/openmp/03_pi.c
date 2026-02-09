#include <omp.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

const int N_COLUMNS_PER_THREADS = 100000;

/**
 * Pi
 *
 * gcc 03_pi.c -o 03_pi -fopenmp -lm
 */
int main(int argc, char* argv[])
{
  double pi;

  pi = 0.0;

  printf(":: Start!\n");
  #pragma omp parallel
  {
    int thread_id;
    int n_threads;
    int a, b;
    int i;
    double x_1, x_2;
    double f_1, f_2;
    double s;

    s = 0.0;
    thread_id = omp_get_thread_num();
    n_threads = omp_get_num_threads();
    a = thread_id * N_COLUMNS_PER_THREADS;
    b = a + N_COLUMNS_PER_THREADS;
    for (i = a; i < b - 1; ++i) {
      x_1 = (double)i / (n_threads * N_COLUMNS_PER_THREADS);
      x_2 = (double)(i + 1) / (n_threads * N_COLUMNS_PER_THREADS);
      f_1 = sqrt(1.0 - x_1 * x_1);
      f_2 = sqrt(1.0 - x_2 * x_2);
      s += (x_2 - x_1) * (f_1 + f_2) / 2.0;
    }
    #pragma omp critical
    pi += s;
  }
  pi *= 4.0;
  printf(":: Pi = %lf\n", pi);

  return 0;
}

// Check [a, b] intervals!
// Use command line argument!
// #pragma omp atomic
