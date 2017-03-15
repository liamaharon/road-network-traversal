/* * * * * * *
 * Module for functions that solve the coding tasks from assignment 1
 *
 * created for COMP20007 Design of Algorithms - Assignment 1, 2017
 * by Liam Aharon <laharon@student.unimelb.edu.au>
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <limits.h>
#include "traverse.h"

/* function prototypes */

void print_path(Graph* graph, int* path, int pathn, int destination_id);

void rec_all_paths(Graph* graph, int destination_id, int* visited, int* path,
int pathn, int edge_destination);

void rec_shortest_path(Graph* graph, int destination_id, int* visited,
int* path, int pathn, int edge_destination, int cur_dist, int* short_dist,
int* short_path, int* short_pathn);

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
  while (!isempty_stack(stack)) {
    // check every edge leading from vertice on top of the stack
    Edge* edge = graph->vertices[peek_stack(stack)]->first_edge;
    while (edge != NULL) {
      // if unvisited vertice push to top of the stack, restart process
      int edge_destination = edge->v;
      if (visited[edge_destination] == 0) {
        printf("%s\n", graph->vertices[edge_destination]->label);
        visited[edge_destination] = 1;
        push_stack(stack, edge_destination);
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
  while (!isempty_queue(queue)) {
    // set first edge of vertice in front of queue
    Edge* edge = graph->vertices[peek_queue(queue)]->first_edge;
    // enqueue and process destinations as soon as we find them, if they are
    // yet to be visited
    while (edge != NULL) {
      int edge_destination = edge->v;
      if (visited[edge_destination] == 0) {
        enqueue_queue(queue, edge_destination);
        visited[edge_destination] = 1;
        printf("%s\n", graph->vertices[edge_destination]->label);
      }
      edge = edge->next_edge;
    }
    // dequeue vertice when we have queued all unseen vertices from its edges
    dequeue_queue(queue);
  }
  free_queue(queue);
  free(visited);
}

// find path between two vertices using depth first search
void detailed_path(Graph* graph, int source_id, int destination_id) {
  const int MAX_VERTICES = graph->maxn;

  // array containing 1 or 0 depending whether or not a vertex has been visited
  int* visited = calloc(sizeof(int), MAX_VERTICES);

  // stack to contain vertices as they're checked
  Stack* stack = new_stack(MAX_VERTICES);

  // push origin vertice id to top of stack, mark visited and print
  // keep track of total weight traveled
  int dist=0;
  push_stack(stack, source_id);
  visited[source_id] = 1;
  printf("%s (%dkm)\n", graph->vertices[source_id]->label, dist);

  // keep looking through stack until is empty
  while (!isempty_stack(stack)) {
    // check every edge leading from vertice on top of the stack
    Edge* edge = graph->vertices[peek_stack(stack)]->first_edge;
    while (edge != NULL) {
      // if unvisited vertice push to top of the stack, restart process
      int edge_destination = edge->v;
      if (visited[edge_destination] == 0) {
        visited[edge_destination] = 1;
        push_stack(stack, edge_destination);
        dist += edge->weight;
        printf("%s (%dkm)\n", graph->vertices[edge_destination]->label, dist);
        // destination found, free and return
        if (edge_destination == destination_id) {
          free(visited);
          free_stack(stack);
          return;
        }
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

void all_paths(Graph* graph, int source_id, int destination_id) {
  const int MAX_VERTICES = graph->maxn;

	int* visited = calloc(sizeof(int), MAX_VERTICES);
  visited[source_id] = 1;
  int* path = calloc(sizeof(int), MAX_VERTICES);
  path[0] = source_id;
  int pathn = 1;

  Edge* edge = graph->vertices[source_id]->first_edge;

  while (edge != NULL) {
    int edge_destination = edge->v;
    if (edge_destination == destination_id) {
      print_path(graph, path, pathn, destination_id);
      printf("\n");
    } else if (!visited[edge_destination]) {
      rec_all_paths(graph, destination_id, visited, path, pathn, edge_destination);
    }
    edge = edge->next_edge;
  }
  free(visited);
  free(path);
}

// recursive call for all_paths - looks through all
void rec_all_paths(Graph* graph, int destination_id, int* visited, int* path,
int pathn, int edge_destination) {
  const int MAX_VERTICES = graph->maxn;
  // make new copies of visited and path
  int* new_visited = calloc(sizeof(int), MAX_VERTICES);
  assert(new_visited);
  memcpy(new_visited, visited, sizeof(int)*MAX_VERTICES);
  int* new_path = calloc(sizeof(int), MAX_VERTICES);
  assert(new_path);
  memcpy(new_path, path, sizeof(int)*MAX_VERTICES);
  new_visited[edge_destination] = 1;
  new_path[pathn] = edge_destination;
  pathn++;

  Edge* edge = graph->vertices[edge_destination]->first_edge;
  while (edge != NULL) {
    int edge_destination = edge->v;
    if (edge_destination == destination_id) {
      print_path(graph, new_path, pathn, destination_id);
      printf("\n");
    } else if (!visited[edge_destination]) {
      rec_all_paths(graph, destination_id, new_visited, new_path, pathn, edge_destination);
    }
    edge = edge->next_edge;
  }
  free(new_visited);
  free(new_path);
}

void print_path(Graph* graph, int* path, int pathn, int destination_id) {
  for (int i=0; i<pathn; i++) {
    printf("%s, ", graph->vertices[path[i]]->label);
  }
  printf("%s", graph->vertices[destination_id]->label);
}

void shortest_path(Graph* graph, int source_id, int destination_id) {
  const int MAX_VERTICES = graph->maxn;

  int* short_path = calloc(sizeof(int), MAX_VERTICES);
  int short_pathn = 0;
  int short_dist = INT_MAX;
	int* visited = calloc(sizeof(int), MAX_VERTICES);
  int* path = calloc(sizeof(int), MAX_VERTICES);

  path[0] = source_id;
  int pathn = 1;
  visited[source_id] = 1;
  Edge* edge = graph->vertices[source_id]->first_edge;
  while (edge != NULL) {
    int cur_dist = edge->weight;
    int edge_destination = edge->v;
    if (edge_destination == destination_id && cur_dist < short_dist) {
      short_pathn = pathn;
      short_dist = cur_dist;
      memcpy(short_path, path, sizeof(int)*MAX_VERTICES);
    } else if (!visited[edge_destination]) {
      rec_shortest_path(graph, destination_id, visited, path, pathn,
      edge_destination, cur_dist, &short_dist, short_path, &short_pathn);
    }
    edge = edge->next_edge;
  }
  print_path(graph, short_path, short_pathn, destination_id);
  printf(" (%dkm)\n", short_dist);
  free(visited);
  free(path);
  free(short_path);
}

void
rec_shortest_path(Graph* graph, int destination_id, int* visited, int* path,
int pathn, int edge_destination, int cur_dist, int* short_dist,
int* short_path, int* short_pathn) {

  const int MAX_VERTICES = graph->maxn;
  // make new copies of visited and path
  int* new_visited = calloc(sizeof(int), MAX_VERTICES);
  assert(new_visited);
  memcpy(new_visited, visited, sizeof(int)*MAX_VERTICES);
  int* new_path = calloc(sizeof(int), MAX_VERTICES);
  assert(new_path);
  memcpy(new_path, path, sizeof(int)*MAX_VERTICES);
  new_visited[edge_destination] = 1;
  new_path[pathn] = edge_destination;
  pathn++;

  Edge* edge = graph->vertices[edge_destination]->first_edge;
  while (edge != NULL) {
    int new_dist = cur_dist + edge->weight;
    int edge_destination = edge->v;
    if (edge_destination == destination_id && new_dist < *short_dist) {
      *short_pathn = pathn;
      *short_dist = new_dist;
      memcpy(short_path, new_path, sizeof(int)*MAX_VERTICES);
    } else if (!visited[edge_destination]) {
      rec_shortest_path(graph, destination_id, new_visited, new_path, pathn,
      edge_destination, new_dist, short_dist, short_path, short_pathn);
    }
    edge = edge->next_edge;
  }
  free(new_visited);
  free(new_path);
}
