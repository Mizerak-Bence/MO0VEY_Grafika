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
void* wait_random_time(void* param)
{
  pthread_t thread;
  int wait_time;

  thread = pthread_self();
  wait_time = (int)(param);
  printf("[%p] Wait %d seconds ...\n", thread.p, wait_time);
  sleep(wait_time);
  printf("[%p] Ready!\n", thread.p);
}

/**
 * Main
 */
int main(int argc, char* argv[])
{
  pthread_t threads[N_THREADS];
  int wait_time;
  int i;

  srand(time(0));

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
