/* * * * * * *
 * Module for creating and manipulating stacks
 *
 * created for COMP20007 Design of Algorithms - Assignment 1, 2017
 * by Liam Aharon <laharon@student.unimelb.edu.au>
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "stack.h"

 /* function definitions */

// create a new, empty stack of ints
Stack*
new_stack(int maxn) {
  //allocate memory to store the stack
  Stack* stack = malloc(sizeof(*stack));
  assert(stack);
  stack->front = -1;
  stack->maxn = maxn;

  // allocate memory to store ints in the stack
  stack->arr = malloc(sizeof(int)*maxn);
  assert(stack->arr);

  return stack;
}

// push a int to the top of a stack
void
push_stack(Stack* stack, int n) {
  // check stack is valid
  assert(stack);
  int front = (stack->front)++;
  assert(front <= stack->maxn);

  stack->arr[front] = n;
}

// return int at the front of the stack
int
peek_stack(Stack* stack) {
  assert(stack);
  if (stack->front == -1) {
    printf("WARNING: Peeked stack is empty.\n");
    return NULL;
  }
  return (stack->arr[stack->front]);
}

// pop front off the stack
int
pop_stack(Stack* stack) {
  // make sure there is at least 1 int in the stack
  assert(stack);
  assert(stack->front >= 0);
  int front = stack->front;
  // return front of the stack and deincrement front
  int n = stack->arr[front];
  (stack->front)--;
  return n;
}
