#include "stack.h"

#include <stdio.h>
#include <stdlib.h>

void init_stack(Stack* stack, int capacity)
{
  stack->capacity = capacity;
  stack->size = 0;
  stack->data = (long*)malloc(sizeof(long) * capacity);
  pthread_mutex_init(&stack->mutex, NULL);
}

void push_into_stack(Stack* stack, long value)
{
  if (stack->size < stack->capacity) {
    // pthread_mutex_lock(&(stack->mutex));
    stack->data[stack->size] = value;
    ++stack->size;
    // pthread_mutex_unlock(&(stack->mutex));
  }
  else {
    printf("ERROR: The stack is full!\n");
  }
}

long pop_from_stack(Stack* stack)
{
  long value;

  if (stack->size > 0) {
    // pthread_mutex_lock(&(stack->mutex));
    --stack->size;
    value = stack->data[stack->size];
    // pthread_mutex_unlock(&(stack->mutex));
    return value;
  }
  else {
    printf("ERROR: The stack is empty!\n");
    return 0;
  }
}
