#include <omp.h>

#include <stdio.h>

/**
 * Hello, OpenMP!
 *
 * gcc 01_hello.c -o 01_hello -fopenmp
 */
int main(int argc, char* argv[])
{
  #pragma omp parallel
  {
    int thread_id;
    thread_id = omp_get_thread_num();
    printf("thread_id = %d\n", thread_id);
  }
  return 0;
}

// #pragma omp parallel num_threads(2)
