#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

void jail(bool is_savior)
{
  static bool is_locked = true;

  if (is_savior == false) {
    while (is_locked) {
      printf("[Prisoner] Help me!\n");
      sleep(1);
    }
    printf("[Prisoner] Thank You! :)\n");
  } else {
    sleep(5);
    printf("[Savior] Wait a minute ...\n");
    sleep(5);
    is_locked = false;
    printf("[Savior] Ready!\n");
  }
}

void* prisoner(void* _)
{
  jail(false);
}

void* savior(void* _)
{
  jail(true);
}

/**
 * Main
 */
int main(int argc, char* argv[])
{
  pthread_t prisoner_thread;
  pthread_t savior_thread;

  printf(":: Start threads ...\n");

  pthread_create(&prisoner_thread, NULL, prisoner, NULL);
  pthread_create(&savior_thread, NULL, savior, NULL);

  pthread_join(prisoner_thread, NULL);
  pthread_join(savior_thread, NULL);
}
