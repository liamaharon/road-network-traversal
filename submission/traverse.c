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

void print_detailed_path(Graph* graph, Stack* vertex_stack, Stack* dist_stack);

void rec_all_paths(Graph* graph, int destination_id, int* visited, int* path,
  int pathn, int root_id);

void rec_shortest_path(Graph* graph, int destination_id, int* visited,
  int* path, int pathn, int root_id, int cur_dist, int* short_dist,
  int* short_path, int* short_pathn);

/* function definitions */

// using DFS print every vertex in the graph
void
print_dfs(Graph* graph, int source_id) {
  const int MAX_VERTICES = graph->maxn;

  // array keeping track of which vertices have been visited
  int* visited = calloc(sizeof(int), MAX_VERTICES);

  // stack to store ids of vertices to be processed
  Stack* stack = new_stack(MAX_VERTICES);

  // print origin vertex and process it in order to start a DFS from it
  push_stack(stack, source_id);
  visited[source_id] = 1;
  printf("%s\n", graph->vertices[source_id]->label);

  // keep looking through stack until is empty
  while (!isempty_stack(stack)) {
    // check every edge leading from vertex on top of the stack
    Edge* edge = graph->vertices[peek_stack(stack)]->first_edge;
    while (edge != NULL) {
      int edge_destination = edge->v;
      // unvisited vertex, push to top of the stack, begin searching its edges
      if (visited[edge_destination] == 0) {
        printf("%s\n", graph->vertices[edge_destination]->label);
        visited[edge_destination] = 1;
        push_stack(stack, edge_destination);
        break;
      }
      // destination of cur edge already visited, check the next one
      else {
        edge = edge->next_edge;
      }
    }
    // vertex on top of stack has had all of its edges visited, pop off the
    // stack
    if (edge == NULL) pop_stack(stack);
  }
  free_stack(stack);
  free(visited);
}

// using BFS print every vertex in the graph
void
print_bfs(Graph* graph, int source_id) {
  const int MAX_VERTICES = graph->maxn;

  // array keeping track of which vertices have been visited
  int* visited = calloc(sizeof(int), MAX_VERTICES);

  // queue to store ids of vertices to be processed
  Queue* queue = new_queue(MAX_VERTICES);

  // print source vertex and process it ready to be used as root of BFS
  enqueue_queue(queue, source_id);
  visited[source_id] = 1;
  printf("%s\n", graph->vertices[source_id]->label);

  // keep looking through queue until is empty
  while (!isempty_queue(queue)) {
    // set first edge of vertex in front of queue
    Edge* edge = graph->vertices[peek_queue(queue)]->first_edge;
    // enqueue and process destinations as soon as we find them, if they are
    // yet to be visited
    while (edge != NULL) {
      int edge_destination = edge->v;
      // unvisited vertex, push to top of queue but keep checking other edges
      if (visited[edge_destination] == 0) {
        enqueue_queue(queue, edge_destination);
        visited[edge_destination] = 1;
        printf("%s\n", graph->vertices[edge_destination]->label);
      }
      edge = edge->next_edge;
    }
    // dequeue vertex when we have queued all unseen vertices from its edges
    dequeue_queue(queue);
  }
  free_queue(queue);
  free(visited);
}

// prints a detailed path from vertex at bottom of stack to top of stack
void
print_detailed_path(Graph* graph, Stack* vertex_stack, Stack* dist_stack) {
  const int MAX_VERTICES = graph->maxn;
  // reverse stacks by pushing their values into a new stack
  Stack* rev_vertex_stack = new_stack(MAX_VERTICES);
  Stack* rev_dist_stack = new_stack(MAX_VERTICES);
  while (!isempty_stack(vertex_stack)) {
    push_stack(rev_vertex_stack, pop_stack(vertex_stack));
    push_stack(rev_dist_stack, pop_stack(dist_stack));
  }
  // print the path from origin to destinaton
  int vertex_id, dist=0;
  while (!isempty_stack(rev_vertex_stack)) {
    vertex_id = pop_stack(rev_vertex_stack);
    dist += pop_stack(rev_dist_stack);
    printf("%s (%dkm)\n", graph->vertices[vertex_id]->label, dist);
  }
  // free these tmp reversed stacks
  free_stack(rev_vertex_stack);
  free_stack(rev_dist_stack);
}

// find a path between two vertices using DFS
void
detailed_path(Graph* graph, int source_id, int destination_id) {
  const int MAX_VERTICES = graph->maxn;

  // handle when source_id == destination_id. only path is starting in source
  // ending in source (traversed 0km)
  if (source_id == destination_id) {
    printf("%s (0km)\n", graph->vertices[source_id]->label);
    return;
  }

  // array keeping track of which vertices have been visited, val to keep track
  // of dist traveled
  int* visited = calloc(sizeof(int), MAX_VERTICES);

  // stacks to store ids of vertices to be processed and distances between them
  Stack* vertex_stack = new_stack(MAX_VERTICES);
  Stack* dist_stack = new_stack(MAX_VERTICES);

  // print origin vertex and process it in order to start a DFS from it
  push_stack(vertex_stack, source_id);
  // push 0 as distance for origin vertex as we're already there
  push_stack(dist_stack, 0);
  visited[source_id] = 1;

  // keep looking through vertex_stack until is empty
  while (!isempty_stack(vertex_stack)) {
    // check every edge leading from vertex on top of the vertex_stack
    Edge* edge = graph->vertices[peek_stack(vertex_stack)]->first_edge;
    while (edge != NULL) {
      int edge_destination = edge->v;
      // unvisited vertex, push to top of the vertex_stack, search its edges
      if (visited[edge_destination] == 0) {
        visited[edge_destination] = 1;
        push_stack(vertex_stack, edge_destination);
        push_stack(dist_stack, edge->weight);
        // destination found, free and return
        if (edge_destination == destination_id) {
          print_detailed_path(graph, vertex_stack, dist_stack);
          free_stack(vertex_stack);
          free_stack(dist_stack);
          free(visited);
          return;
        }
        // move onto checking new node in stack instead of other edges
        break;
      }
      // if vertex leading from edge already seen check the next edge.
      else {
        edge = edge->next_edge;
      }
    }
    // vertex on top of stack has had all of its edges visited, with no path
    // to destination. pop it and distance to it
    if (edge == NULL) {
      pop_stack(vertex_stack);
      pop_stack(dist_stack);
    }
  }
  // free memory in the case destinaton is inaccessible from source
  free_stack(vertex_stack);
  free(visited);
}

// prints every possible path from source to destination using DFS
void
all_paths(Graph* graph, int source_id, int destination_id) {
  const int MAX_VERTICES = graph->maxn;

  // initalise arrays to keep track of the path so far, and which vertices have
  // been visited
	int* visited = calloc(sizeof(int), MAX_VERTICES);
  int* path = calloc(sizeof(int), MAX_VERTICES);

  // assign infomation from root node to necessary areas in order to begin
  // searching from it
  int pathn = 1;
  visited[source_id] = 1;
  path[0] = source_id;

  // starting with the first edge, begin searching through every edge in the
  // graph for the destination, all while keeping track of the path taken
  Edge* edge = graph->vertices[source_id]->first_edge;
  while (edge != NULL) {
    int edge_destination = edge->v;
    // destination found adjacent to source, print
    if (edge_destination == destination_id) {
      print_path(graph, path, pathn, destination_id);
      printf("\n");
    // undiscovered non-destination vertex found, recurse on it
    } else if (!visited[edge_destination]) {
      rec_all_paths(graph, destination_id, visited, path, pathn,
        edge_destination);
    }
    // finised on this edge, check the next one
    edge = edge->next_edge;
  }
  free(visited);
  free(path);
}

// recursive call for all_paths, using DFS looks through queue
void
rec_all_paths(Graph* graph, int destination_id, int* visited, int* path,
int pathn, int root_id) {
  const int MAX_VERTICES = graph->maxn;

  // in order to not change parent visited and path arrays we duplicate here
  int* new_visited = calloc(sizeof(int), MAX_VERTICES);
  assert(new_visited);
  memcpy(new_visited, visited, sizeof(int)*MAX_VERTICES);
  int* new_path = calloc(sizeof(int), MAX_VERTICES);
  assert(new_path);
  memcpy(new_path, path, sizeof(int)*MAX_VERTICES);

  // process values from root vertex and begin DFS on its edges
  new_visited[root_id] = 1;
  new_path[pathn] = root_id;
  pathn++;
  Edge* edge = graph->vertices[root_id]->first_edge;
  while (edge != NULL) {
    int edge_destination = edge->v;
    // destination found. print and move on
    if (edge_destination == destination_id) {
      print_path(graph, new_path, pathn, destination_id);
      printf("\n");
    // undiscovered non-destination vertex found, recurse on it
    } else if (!visited[edge_destination]) {
      rec_all_paths(graph, destination_id, new_visited, new_path, pathn,
        edge_destination);
    }
    // check next edge
    edge = edge->next_edge;
  }
  // free heap from this recursive instance before it pops off the stack
  free(new_visited);
  free(new_path);
}

// prints the path from source to destinaton specified in the path array
void
print_path(Graph* graph, int* path, int pathn, int destination_id) {
  int i;
  for (i=0; i<pathn; i++) {
    printf("%s, ", graph->vertices[path[i]]->label);
  }
  printf("%s", graph->vertices[destination_id]->label);
}

// prints the shortest path from source_id to destination_id from graph
void
shortest_path(Graph* graph, int source_id, int destination_id) {
  const int MAX_VERTICES = graph->maxn;

  // initalise values to keep track of the path so far, which vertices has
  // been visited and infomation about the shortest path
  int* short_path = calloc(sizeof(int), MAX_VERTICES);
  int short_pathn = 0;
  int short_dist = INT_MAX;
	int* visited = calloc(sizeof(int), MAX_VERTICES);
  int* path = calloc(sizeof(int), MAX_VERTICES);

  // assign infomation from root node to necessary areas in order to begin
  // searching from it
  path[0] = source_id;
  int pathn = 1;
  visited[source_id] = 1;
  Edge* edge = graph->vertices[source_id]->first_edge;
  // using DFS and keeping track of paths and distances at every vertex
  // begin searching the array
  while (edge != NULL) {
    int cur_dist = edge->weight;
    int edge_destination = edge->v;
    // cur path shortest so far, set shortest path values to cur path values
    if (edge_destination == destination_id && cur_dist < short_dist) {
      short_pathn = pathn;
      short_dist = cur_dist;
      memcpy(short_path, path, sizeof(int)*MAX_VERTICES);
    // undiscovered non-destination vertex found, recurse on it
    } else if (!visited[edge_destination]) {
      rec_shortest_path(graph, destination_id, visited, path, pathn,
      edge_destination, cur_dist, &short_dist, short_path, &short_pathn);
    }
    // finised on this edge, check the next one
    edge = edge->next_edge;
  }
  // finished searching entire graph. our shortest path values must now be
  // accurate, go ahead print shortest path and clean up
  print_path(graph, short_path, short_pathn, destination_id);
  printf(" (%dkm)\n", short_dist);
  free(visited);
  free(path);
  free(short_path);
}

// recursive call for shortest_path, using DFS looks through queue
void
rec_shortest_path(Graph* graph, int destination_id, int* visited, int* path,
int pathn, int root_id, int cur_dist, int* short_dist,
int* short_path, int* short_pathn) {
  const int MAX_VERTICES = graph->maxn;

// in order to not change parent visited and path arrays we duplicate here
  int* new_visited = calloc(sizeof(int), MAX_VERTICES);
  assert(new_visited);
  memcpy(new_visited, visited, sizeof(int)*MAX_VERTICES);
  int* new_path = calloc(sizeof(int), MAX_VERTICES);
  assert(new_path);
  memcpy(new_path, path, sizeof(int)*MAX_VERTICES);

  // process values from root vertex and begin DFS on its edges
  new_visited[root_id] = 1;
  new_path[pathn] = root_id;
  pathn++;
  Edge* edge = graph->vertices[root_id]->first_edge;
  while (edge != NULL) {
    int new_dist = cur_dist + edge->weight;
    int edge_destination = edge->v;
    // current path is shortest path found so far. copy values and move on
    if (edge_destination == destination_id && new_dist < *short_dist) {
      *short_pathn = pathn;
      *short_dist = new_dist;
      memcpy(short_path, new_path, sizeof(int)*MAX_VERTICES);
    // undiscovered non-destination vertex found, recurse on it
    } else if (!visited[edge_destination]) {
      rec_shortest_path(graph, destination_id, new_visited, new_path, pathn,
      edge_destination, new_dist, short_dist, short_path, short_pathn);
    }
    // check next edge
    edge = edge->next_edge;
  }
  // free heap from this recursive instance before it pops off the stack
  free(new_visited);
  free(new_path);
}
