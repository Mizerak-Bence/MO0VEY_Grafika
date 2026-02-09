#include "sudoku.h"

#include <pthread.h>
#include <stdbool.h>

void solve(int table[9][9], int start_i, int start_j)
{
  int i, j, k;

  i = start_i;
  j = start_j;

  if (i == 9) {
    if (is_valid(table)) {
      // print_table(table);
    }
    else {
      printf("There is no solution!\n");
    }
  }
  else {
    if (table[i][j] == 0) {
      for (k = 1; k <= 9; ++k) {
        table[i][j] = k;
        if (is_valid(table)) {
          if (j < 8) {
            solve(table, i, j + 1);
          }
          else {
            solve(table, i + 1, 0);
          }
        }
        table[i][j] = 0;
      }
    }
    else {
      if (j < 8) {
        solve(table, i, j + 1);
      }
      else {
        solve(table, i + 1, 0);
      }
    }
  }
}

void solve_in_threads(int table[9][9], int start_i, int start_j)
{
  Task tasks[9];
  pthread_t threads[9];
  int thread_index;
  int i, j;

  for (thread_index = 0; thread_index < 9; ++thread_index) {
    for (i = 0; i < 9; ++i) {
      for (j = 0; j < 9; ++j) {
        tasks[thread_index].table[i][j] = table[i][j];
      }
    }
    tasks[thread_index].table[start_i][start_j] = thread_index + 1;
    tasks[thread_index].start_i = start_i;
    tasks[thread_index].start_j = start_j;
    pthread_create(&threads[thread_index], NULL, solve_wrapper, &tasks[thread_index]);
  }
  for (thread_index = 0; thread_index < 9; ++thread_index) {
    pthread_join(threads[thread_index], NULL);
  }
}

void solve_wrapper(Task* task)
{
  solve(task->table, task->start_i, task->start_j);
}

void print_table(int table[9][9])
{
  int i, j;

  for (i = 0; i < 9; ++i) {
    for (j = 0; j < 9; ++j) {
      printf("%d ", table[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

bool is_valid(int table[9][9])
{
  return is_valid_rows(table)
    && is_valid_columns(table)
    && is_valid_blocks(table);
}

bool is_valid_rows(int table[9][9])
{
  int i, j, k;
  int counts[10];

  for (i = 0; i < 9; ++i) {
    for (k = 0; k < 10; ++k) {
      counts[k] = 0;
    }
    for (j = 0; j < 9; ++j) {
      // TODO: Check not zero!
      ++counts[table[i][j]];
    }
    for (k = 1; k < 10; ++k) {
      if (counts[k] > 1) {
        return false;
      }
    }
  }
  return true;
}

bool is_valid_columns(int table[9][9])
{
  int i, j, k;
  int counts[10];

  for (i = 0; i < 9; ++i) {
    for (k = 0; k < 10; ++k) {
      counts[k] = 0;
    }
    for (j = 0; j < 9; ++j) {
      // TODO: Check not zero!
      ++counts[table[j][i]];
    }
    for (k = 1; k < 10; ++k) {
      if (counts[k] > 1) {
        return false;
      }
    }
  }
  return true;
}

bool is_valid_blocks(int table[9][9])
{
  int block_i, block_j, i, j, k;
  int counts[10];

  for (block_i = 0; block_i < 9; block_i += 3) {
    for (block_j = 0; block_j < 9; block_j += 3) {
      for (k = 0; k < 10; ++k) {
        counts[k] = 0;
      }
      for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
          // TODO: Check not zero!
          ++counts[table[block_i + i][block_j + j]];
        }
      }
      for (k = 1; k < 10; ++k) {
        if (counts[k] > 1) {
          return false;
        }
      }
    }
  }
  return true;
}
