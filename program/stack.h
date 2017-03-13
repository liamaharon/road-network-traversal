/* * * * * * *
 * Module for creating and manipulating stacks
 *
 * created for COMP20007 Design of Algorithms - Assignment 1, 2017
 * by Liam Aharon <laharon@student.unimelb.edu.au>
 */

#include "graph.h"

typedef struct stack Stack;

struct stack {
  Vertex** vertexarr;
  int front;
  int maxn;
};

 /* function prototypes */

Stack* new_stack(int maxn);

void push_stack(Stack* stack, Vertex* vertex);

Vertex* peek_stack(Stack* stack);

Vertex* pop_stack(Stack* stack);

void free_stack(Stack* stack);
