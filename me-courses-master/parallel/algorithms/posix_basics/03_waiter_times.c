#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

const int N_THREADS = 20;

clock_t start_time;

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

/**
 * Wait random time.
 */
void* wait_random_time(void* param)
{
  pthread_t thread;
  int wait_time;

  wait_time = (int)param;
  thread = pthread_self();
  printf("[%p] Wait %d seconds ... (%lf)\n", thread.p, wait_time, get_time());
  sleep(wait_time);
  printf("[%p] Ready! (%f)\n", thread.p, get_time());
}

/**
 * Main
 */
int main(int argc, char* argv[])
{
  pthread_t threads[N_THREADS];
  int wait_time;
  int i;

  start_time = clock();

  printf(":: Start threads ...\n");
  for (i = 0; i < N_THREADS; ++i) {
    wait_time = rand() % 10 + 1;
    pthread_create(&threads[i], NULL, wait_random_time, (void*)wait_time);
  }

  printf(":: Join threads ...\n");
  for (i = 0; i < N_THREADS; ++i) {
    pthread_join(threads[i], NULL);
  }

  printf(":: Ready.\n");

  return 0;
}
