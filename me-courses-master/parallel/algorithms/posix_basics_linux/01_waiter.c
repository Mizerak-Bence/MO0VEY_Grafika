#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

const int N_THREADS = 5;

/**
 * Wait random time.
 */
void* wait_random_time(void* _)
{
  pthread_t thread;
  pid_t tid;
  int wait_time;

  thread = pthread_self();
  tid = gettid();

  wait_time = rand() % 10 + 1;
  printf("[%d] Wait %d seconds ...\n", tid, wait_time);
  sleep(wait_time);
  printf("[%d] Ready!\n", tid);
}

/**
 * Main
 */
int main(int argc, char* argv[])
{
  pthread_t threads[N_THREADS];
  int i;

  printf(":: Start threads ...\n");
  for (i = 0; i < N_THREADS; ++i) {
    pthread_create(&threads[i], NULL, wait_random_time, NULL);
  }

  printf(":: Join threads ...\n");
  for (i = 0; i < N_THREADS; ++i) {
    pthread_join(threads[i], NULL);
  }

  printf(":: Ready.\n");

  return 0;
}
