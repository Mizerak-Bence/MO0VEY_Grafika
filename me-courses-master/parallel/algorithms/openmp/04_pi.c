#include <omp.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

const int N_COLUMNS = 100000;

/**
 * Pi
 *
 * gcc 04_pi.c -o 04_pi -fopenmp -lm
 */
int main(int argc, char* argv[])
{
  double pi;

  pi = 0.0;

  printf(":: Start!\n");
  #pragma omp parallel
  {
    double s;
    int i;
    s = 0.0;
    #pragma omp for
    for (i = 0; i < N_COLUMNS - 1; ++i) {
      double x_1 = (double)i / N_COLUMNS;
      double x_2 = (double)(i + 1) / N_COLUMNS;
      double f_1 = sqrt(1.0 - x_1 * x_1);
      double f_2 = sqrt(1.0 - x_2 * x_2);
      s += (x_2 - x_1) * (f_1 + f_2) / 2.0;
    }
    #pragma omp critical
    pi += s;
  }

  pi *= 4.0;
  printf(":: Pi = %lf\n", pi);

  return 0;
}
