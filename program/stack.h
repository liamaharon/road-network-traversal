/* * * * * * *
 * Module for creating and manipulating stacks
 *
 * created for COMP20007 Design of Algorithms - Assignment 1, 2017
 * by Liam Aharon <laharon@student.unimelb.edu.au>
 */

#include "graph.h"

typedef struct stack Stack;

struct stack {
  int arr[];
  int front;
  int maxn;
};

 /* function prototypes */

Stack* new_stack(int maxn);

void push_stack(Stack* stack, int n);

Vertex* peek_stack(Stack* stack);

Vertex* pop_stack(Stack* stack);
