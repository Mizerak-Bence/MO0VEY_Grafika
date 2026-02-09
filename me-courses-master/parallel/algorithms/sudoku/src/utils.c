#include "utils.h"

double calc_elapsed_time(struct timespec* start_time, struct timespec* finish_time)
{
  double elapsed_time;

  elapsed_time = (finish_time->tv_sec - start_time->tv_sec);
  elapsed_time += (double)(finish_time->tv_nsec - start_time->tv_nsec) / 1000000000;

  return elapsed_time;
}
