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
 * Merge the arrays.
 */
void merge(int* values, int left_length, int right_length)
{
  int* temp;
  int left_index, right_index, result_index;
  int length;
  int array_size;

  printf(">>> %d + %d\n", left_length, right_length);

  length = left_length + right_length;
  array_size = length * sizeof(int);
  temp = (int*)malloc(array_size);
  memcpy(temp, values, array_size);

  left_index = 0;
  right_index = left_length;
  result_index = 0;
  while (left_index < left_length && right_index < length) {
    if (temp[left_index] < temp[right_index]) {
      values[result_index] = temp[left_index];
      ++left_index;
    } else {
      values[result_index] = temp[right_index];
      ++right_index;
    }
    ++result_index;
  }
  while (left_index < left_length) {
    values[result_index] = temp[left_index];
    ++left_index;
    ++result_index;
  }
  while (right_index < length) {
    values[result_index] = temp[right_index];
    ++right_index;
    ++result_index;
  }

  free(temp);
}

/**
 * Sort the values by merge sort.
 */
void mergesort(int* values, int p, int r)
{
  int q;

  if (p < r) {
    q = (p + r) / 2;
    printf("(%d, %d, %d)\n", p, q, r);
    mergesort(values, p, q);
    mergesort(values, q + 1, r);
    merge(values + p, q - p + 1, r - q);
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


  size = 100;
  data = generate_data(size);
  for (i = 0; i < size; ++i) {
    // printf(":: data[%d] = %d\n", i, data[i]);
  }
  mergesort(data, 0, size - 1);
  for (i = 0; i < size; ++i) {
    // printf(":: data[%d] = %d\n", i, data[i]);
  }
  free(data);
}
