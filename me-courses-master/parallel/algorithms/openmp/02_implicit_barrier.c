#include <omp.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

/**
 * Implicit barrier
 */
int main(int argc, char* argv[])
{
  srand(time(0));
  printf(":: Start!\n");
  #pragma omp parallel
  {
    int thread_id;
    int wait_time;
    int i;
    thread_id = omp_get_thread_num();
    for (i = 0; i < thread_id + 1; ++i) {
      wait_time = rand() % 10 + 1;
    }
    printf("[%d] Wait %d seconds ...\n", thread_id, wait_time);
    sleep(wait_time);
    printf("[%d] Ok.\n", thread_id);
  }
  printf(":: Ready!\n");

  return 0;
}
