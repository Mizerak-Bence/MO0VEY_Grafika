#include <omp.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * Locks
 */
int main(int argc, char* argv[])
{
  int thread_id;
  int n_threads;
  omp_lock_t lock;
  int counter;
  int value;

  counter = 10;
  // omp_init_lock(&lock);
  #pragma omp parallel private (thread_id, value)
  {
    thread_id = omp_get_thread_num();

    #pragma omp single
    n_threads = omp_get_num_threads();
    printf("[%d] Number of threads: %d\n", thread_id, n_threads);
    sleep(1);
    #pragma omp barrier

    // omp_set_lock(&lock);
    value = counter;
    printf("[%d] Read value %d\n", thread_id, value);
    sleep(1);
    ++value;
    printf("[%d] Increment value %d\n", thread_id, value);
    sleep(1);
    counter = value;
    printf("[%d] Update counter to: %d\n", thread_id, value);
    // omp_unset_lock(&lock);
  }
  printf(":: counter = %d\n", counter);

  // omp_destroy_lock(&lock);

  return 0;
}
