#include "stack.h"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#define N_THREADS 200
#define N_TRIALS 1000

/**
 * This is the shared stack.
 */
Stack g_stack;

/**
 * Task of a worker thread.
 */
void* worker(void* _)
{
  int value;
  int resulted_value;

  for (value = 0; value < N_TRIALS; ++value) {
    push_into_stack(&g_stack, value);
  }

  return NULL;
}

/**
 * Demonstration of the Lost Update problem via a stack.
 */
int main(int argc, char* argv[])
{
  pthread_t threads[N_THREADS];
  int i;
  int* counts;

  printf("Initialize the stack ...\n");
  init_stack(&g_stack, N_THREADS * N_TRIALS);

  printf("Start the simulation ...\n");
  for (i = 0; i < N_THREADS; ++i) {
    pthread_create(&threads[i], NULL, worker, NULL);
  }
  for (i = 0; i < N_THREADS; ++i) {
    pthread_join(threads[i], NULL);
  }

  printf("Check the results ...\n");
  counts = (int*)calloc(N_TRIALS, sizeof(int));
  for (i = 0; i < g_stack.size; ++i) {
    ++counts[g_stack.data[i]];
  }
  for (i = 0; i < N_TRIALS; ++i) {
    if (counts[i] != N_THREADS) {
      printf("ERROR: Invalid stack!\n");
    }
  }
  free(counts);

  printf("Ready!\n");

  return 0;
}
