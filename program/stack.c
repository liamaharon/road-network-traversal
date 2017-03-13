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

// create a new, empty stack of vertex pointers
Stack*
new_stack(int maxn) {
  //allocate memory to store the stack
  Stack* stack = malloc(sizeof(*stack));
  assert(stack);
  stack->front = -1;
  stack->maxn = maxn;

  // allocate memory to store vertexs pointers in the stack
  stack->vertexarr = malloc(sizeof(Vertex*)*maxn);
  assert(stack->vertexarr);

  return stack;
}

// push a vertex to the top of a stack
void
push_stack(Stack* stack, Vertex* vertex) {
  // check stack & vertex exists and stack is not full
  assert(stack && vertex);
  int front = (stack->front)++;
  assert(front <= stack->maxn);

  stack->vertexarr[front] = vertex;
}

// return a pointer to the vertex at the top of the stack
Vertex*
peek_stack(Stack* stack) {
  assert(stack);
  if (stack->front == -1) {
    printf("WARNING: Peeked stack is empty.\n");
    return NULL;
  }
  return (stack->vertexarr[stack->front]);
}

// pop vertex off the stack
Vertex*
pop_stack(Stack* stack) {
  // make sure there is at least 1 vertex in the stack
  assert(stack);
  assert(stack->front >= 0);
  int front = stack->front;
  // take pointer of vertex at front of the stack, deincrement front
  // and return
  Vertex* vertex = stack->vertexarr[front];
  (stack->front)--;
  return vertex;
}

void free_stack(Stack* stack) {
  free(stack);
}
