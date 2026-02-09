#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

int shared_value;

void* increment_by_a(void* _)
{
  int value;

  sleep(1);
  printf("[ A ] Read value %d.\n", shared_value);
  value = shared_value;
  sleep(1);
  ++value;
  printf("[ A ] Incremented value: %d.\n", value);
  sleep(1);
  printf("[ A ] Write back to shared.\n");
  shared_value = value;
}

void* increment_by_b(void* _)
{
  int value;

  sleep(2);
  printf("[ B ] Read value %d.\n", shared_value);
  value = shared_value;
  sleep(1);
  ++value;
  printf("[ B ] Incremented value: %d.\n", value);
  sleep(1);
  printf("[ B ] Write back to shared.\n");
  shared_value = value;
}

/**
 * Main
 */
int main(int argc, char* argv[])
{
  pthread_t thread_a, thread_b;

  shared_value = 100;

  printf(":: Start threads A ...\n");
  pthread_create(&thread_a, NULL, increment_by_a, NULL);
  printf(":: Start threads B ...\n");
  pthread_create(&thread_b, NULL, increment_by_b, NULL);

  printf(":: Join thread A ...\n");
  pthread_join(thread_a, NULL);
  printf(":: Join thread B ...\n");
  pthread_join(thread_b, NULL);

  printf(":: shared_value = %d\n", shared_value);

  printf(":: Ready.\n");

  return 0;
}
