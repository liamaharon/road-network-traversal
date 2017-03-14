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

  // push origin vertice id to top of stack, mark visited and print
  push_stack(stack, source_id);
  visited[source_id] = 1;
  printf("%s\n", graph->vertices[source_id]->label);

  // keep looking through stack until is empty
  while (stack->front != -1) {
    // check every edge leading from vertice on top of the stack
    Edge* edge = graph->vertices[peek_stack(stack)]->first_edge;
    while (edge != NULL) {
      // if unvisited vertice push to top of the stack, restart process
      int destination_id = edge->v;
      if (visited[destination_id] == 0) {
        printf("%s\n", graph->vertices[destination_id]->label);
        visited[destination_id] = 1;
        push_stack(stack, destination_id);
        break;
      }
      // if vertice leading from edge already seen check the next edge.
      else {
        edge = edge->next_edge;
      }
    }
    // once edges of vertice on top of stack are all visited, pop it from
    // the stack
    if (edge == NULL) pop_stack(stack);
  }
  free_stack(stack);
  free(visited);
}

void print_bfs(Graph* graph, int source_id) {
  const int MAX_VERTICES = graph->maxn;

  // array containing 1 or 0 depending whether or not a vertex has been visited
  int* visited = calloc(sizeof(int), MAX_VERTICES);

  // queue to store ids of vertices to be processed
  Queue* queue = new_queue(MAX_VERTICES);

  // enqueue source vertice to queue, mark as visited and print it
  enqueue_queue(queue, source_id);
  visited[source_id] = 1;
  printf("%s\n", graph->vertices[source_id]->label);

  // keep looking through queue until is empty
  while (isempty_queue(queue) != 1) {
    // set first edge of vertice in front of queue
    Edge* edge = graph->vertices[peek_queue(queue)]->first_edge;
    // enqueue and process destinations as soon as we find them, if they are
    // yet to be visited
    while (edge != NULL) {
      int destination_id = edge->v;
      if (visited[destination_id] == 0) {
        enqueue_queue(queue, destination_id);
        visited[destination_id] = 1;
        printf("%s\n", graph->vertices[destination_id]->label);
      }
      edge = edge->next_edge;
    }
    // dequeue vertice when we have queued all unseen vertices from its edges
    dequeue_queue(queue);
  }
  free_queue(queue);
  free(visited);
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
