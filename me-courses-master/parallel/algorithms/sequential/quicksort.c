#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/**
 * Generate the data for experimentation.
 */
int* generate_data(unsigned long size)
{
  int* data;
  int i;

  data = (int*)malloc(size * sizeof(int));
  for (i = 0; i < size; ++i) {
    data[i] = 100 * (double)(rand()) / RAND_MAX;
  }

  return data;
}

/**
 * Partition the array around the pivot element.
 */
int partition(int* values, int p, int r, int x)
{
  int i, j;
  int temp;

  i = p - 1;
  j = r + 1;
  while (i < j) {
    do {
      ++i;
    } while (values[i] < x);
    do {
      --j;
    } while (values[j] > x);
    if (i < j) {
      temp = values[i];
      values[i] = values[j];
      values[j] = temp;
    }
  }

  return j;
}

/**
 * Sort the element in the given interval.
 */
void quicksort(int* values, int p, int r)
{
  int q;

  if (p < r) {
    q = partition(values, p, r, values[p]);
    // printf("q = %d\n", q);
    quicksort(values, p, q);
    quicksort(values, q + 1, r);
  }
}

/**
 * Main
 */
int main(int argc, char* argv[])
{
  int* data;
  int size;
  int i;

  size = 10;
  data = generate_data(size);
  for (i = 0; i < size; ++i) {
    printf(":: data[%d] = %d\n", i, data[i]);
  }
  printf(":: Sort ...\n");
  quicksort(data, 0, size - 1);
  for (i = 0; i < size; ++i) {
    printf(":: data[%d] = %d\n", i, data[i]);
  }
  free(data);
}
