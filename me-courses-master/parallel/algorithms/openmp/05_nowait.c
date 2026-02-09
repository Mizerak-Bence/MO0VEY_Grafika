#include <omp.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

const int N_SLEEPS = 4;

/**
 * No wait!
 */
int main(int argc, char* argv[])
{
  int i;
  srand(time(0));
  #pragma omp parallel
  {
    #pragma omp for
    for (i = 0; i < N_SLEEPS; ++i) {
      int thread_id;
      int wait_time;
      int j;
      thread_id = omp_get_thread_num();
      for (j = 0; j < thread_id + 1; ++j) {
        wait_time = rand() % 10 + 1;
      }
      printf("[%d] Wait %d seconds ... (%d)\n", thread_id, wait_time, i + 1);
      sleep(wait_time);
      printf("[%d] Ok.\n", thread_id);
    }
    printf("After the for loop.\n");
  }
  printf(":: Ready!\n");
  return 0;
}

// DEMO: #pragma omp for nowait
// DEMO: const int N_SLEEPS = 6;
