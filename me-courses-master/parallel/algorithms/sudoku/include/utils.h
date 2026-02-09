#ifndef UTILS_H
#define UTILS_H

#include <time.h>

/**
 * Calculate the elapsed time between the given two time points.
 */
double calc_elapsed_time(struct timespec* start_time, struct timespec* finish_time);

#endif // UTILS_H
