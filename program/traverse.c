/* * * * * * *
 * Module for functions that solve the coding tasks from assignment 1
 *
 * created for COMP20007 Design of Algorithms - Assignment 1, 2017
 * by Liam Aharon <laharon@student.unimelb.edu.au>
 */

#include <stdio.h>
#include <stdlib.h>
#include "traverse.h"

/* function definitions */

void print_dfs(Graph* graph, int source_id) {
  const int MAX_VERTICES = graph->maxn;

  // array containing 1 or 0 depending whether or not a vertex has been visited
  int* visited = calloc(sizeof(int), MAX_VERTICES);

  // stack to contain vertices as they're checked
  Stack* stack = new_stack(MAX_VERTICES);

  // push origin node_id to top of stack, mark visited and print
  push_stack(stack, source_id);
  visited[source_id] = 1;
  printf("%s\n", graph->vertices[source_id]->label);

  // keep looking through vertices until stack is empty
  while (stack->front != -1) {
    // check every edge leading from the vertice ontop of the stack
    Edge* edge = graph->vertices[peek_stack(stack)]->first_edge;
    while (edge != NULL) {
      // if we find an unvisited vertice push to top of the stack and restart
      // process
      if (visited[edge->v] == 0) {
        printf("%s\n", graph->vertices[edge->v]->label);
        visited[edge->v] = 1;
        push_stack(stack, edge->v);
        break;
      }
      // if vertice leading from edge already seen check the next edge.
      // if seen all vertices remove vertice from stack
      else {
        edge = edge->next_edge;
      }
    }
    if (edge == NULL) pop_stack(stack);
  }
  free_stack(stack);
  free(visited);
}

void print_bfs(Graph* graph, int source_id) {
	printf("not yet implemented: put code for part 2 here\n");
}

void detailed_path(Graph* graph, int source_id, int destination_id) {
	printf("not yet implemented: put code for part 3 here\n");
}

void all_paths(Graph* graph, int source_id, int destination_id) {
	printf("not yet implemented: put code for part 4 here\n");
}

void shortest_path(Graph* graph, int source_id, int destination_id) {
	printf("not yet implemented: put code for part 5 here\n");
}
