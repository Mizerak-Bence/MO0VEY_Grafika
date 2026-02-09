#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

const int N_THREADS = 20;

/**
 * Wait random time.
 */
void* wait_random_time(int* wait_time)
{
  pid_t tid = gettid();

  printf("[%d] Wait %d seconds ...\n", tid, *wait_time);
  sleep(*wait_time);
  printf("[%d] Ready!\n", tid);
}

/**
 * Main
 */
int main(int argc, char* argv[])
{
  pthread_t threads[N_THREADS];
  int wait_times[N_THREADS];
  int i;

  srand(time(0));

  printf(":: Start threads ...\n");
  for (i = 0; i < N_THREADS; ++i) {
    wait_times[i] = rand() % 10 + 1;
    pthread_create(&threads[i], NULL, wait_random_time, (void*)(&wait_times[i]));
  }

  printf(":: Join threads ...\n");
  for (i = 0; i < N_THREADS; ++i) {
    pthread_join(threads[i], NULL);
  }

  printf(":: Ready.\n");

  return 0;
}

