#ifndef STACK_H
#define STACK_H

#include <pthread.h>

/**
 * Stack data structure
 */
typedef struct Stack
{
  long* data;
  int size;
  int capacity;
  pthread_mutex_t mutex;
} Stack;

/**
 * Initialize a new stack.
 */
void init_stack(Stack* stack, int capacity);

/**
 * Push a new element into the stack.
 */
void push_into_stack(Stack* stack, long value);

/**
 * Pop an element from the stack.
 */
long pop_from_stack(Stack* stack);

#endif // STACK_H
