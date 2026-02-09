#ifndef SUDOKU_H
#define SUDOKU_H

#include <stdbool.h>
#include <stdio.h>

/**
 * Description of a task for a thread.
 */
typedef struct Task
{
  int table[9][9];
  int start_i;
  int start_j;
} Task;

/**
 * Solve the Sudoku puzzle.
 */
void solve(int table[9][9], int start_i, int start_j);

/**
 * Solve the Sudoku puzzle in threads.
 */
void solve_in_threads(int table[9][9], int start_i, int start_j);

/**
 * Wrap the task call for thread creation.
 */
void solve_wrapper(Task* task);

/**
 * Print the Sudoku table.
 */
void print_table(int table[9][9]);

/**
 * Check that the table is valid.
 */
bool is_valid(int table[9][9]);

/**
 * Check the rows.
 */
bool is_valid_rows(int table[9][9]);

/**
 * Check the columns.
 */
bool is_valid_columns(int table[9][9]);

/**
 * Check the blocks.
 */
bool is_valid_blocks(int table[9][9]);

#endif // SUDOKU_H
