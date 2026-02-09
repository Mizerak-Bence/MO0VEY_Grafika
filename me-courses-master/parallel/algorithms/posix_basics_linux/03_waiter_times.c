#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

// https://levelup.gitconnected.com/8-ways-to-measure-execution-time-in-c-c-48634458d0f9

const int N_THREADS = 8;

// clock_t start_time;
struct timeval start_time;

/**
 * Calculate the time in seconds from the start of the application.
 */
double get_time()
{
  /*
  clock_t time_diff;
  double time;

  time_diff = clock() - start_time;
  time = (double)(time_diff) / CLOCKS_PER_SEC;

  return time;
  */

  struct timeval end_time;
  gettimeofday(&end_time, 0);

  long seconds = end_time.tv_sec - start_time.tv_sec;
  long microseconds = end_time.tv_usec - start_time.tv_usec;
  double elapsed = seconds + microseconds * 1e-6;

  return elapsed;
}

/**
 * Wait random time.
 */
void* wait_random_time(int* wait_time)
{
  pid_t tid;

  tid = gettid();

  printf("[%d] Wait %d seconds ... (%lf)\n", tid, *wait_time, get_time());
  sleep(*wait_time);
  printf("[%d] Ready! (%lf)\n", tid, get_time());
}

/**
 * Main
 */
int main(int argc, char* argv[])
{
  pthread_t threads[N_THREADS];
  int wait_times[N_THREADS];

  // start_time = clock();
  gettimeofday(&start_time, 0);
  printf("Start time: %lf\n", get_time());

  printf(":: Start threads ...\n");
  for (int i = 0; i < N_THREADS; ++i) {
    wait_times[i] = rand() % 10 + 1;
    pthread_create(&threads[i], NULL, wait_random_time, (void*)(&wait_times[i]));
  }

  printf(":: Join threads ...\n");
  for (int i = 0; i < N_THREADS; ++i) {
    pthread_join(threads[i], NULL);
  }

  printf(":: Ready.\n");

  return 0;
}
