#include <omp.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * Mastery
 */
int main(int argc, char* argv[])
{
  int thread_id;
  #pragma omp parallel private (thread_id)
  {
    thread_id = omp_get_thread_num();
    printf("[%d] A\n", thread_id);
    #pragma omp master
    printf("[%d] I am the master!\n", thread_id);
    #pragma omp barrier
    printf("[%d] B\n", thread_id);
  }
  printf(":: Ready!\n");

  return 0;
}

// #pragma omp single
