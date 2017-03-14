/* * * * * * *
 * Module for creating and manipulating queues using a circular array
 *
 * created for COMP20007 Design of Algorithms - Assignment 1, 2017
 * by Liam Aharon <laharon@student.unimelb.edu.au>
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <assert.h>
 #include "queue.h"

 Queue*
 new_queue(int maxn) {
   Queue* queue = malloc(sizeof(*queue));
   assert(queue);
   queue->maxn = 4;
   queue->size = maxn;
   queue->front = -1;
   queue->rear = -1;
   queue->arr = malloc(sizeof(int)*maxn);
   assert(queue->arr);
   return queue;
 }

void
enqueue_queue(Queue* queue, int num) {
  // empty queue, initalise front and rear values
  if (queue->front == -1) {
    queue->front = 0;
    queue->rear = 0;
  // non-empty queue, increment rear moving to start of queue if required
  } else {
    queue->rear = ((queue->rear)+1) % queue->maxn;
  }
  queue->arr[queue->rear] = num;
}

int
dequeue_queue(Queue* queue) {
  int front_val = queue->arr[queue->front];
  // last val removed from queue, mark as empty
  if (queue->front == queue->rear) {
    queue->front = -1;
    queue->rear = -1;
  } else {
  // queue not empty, increment front moving to begining of queue if required
    queue->front = ((queue->front)+1) % queue->maxn;
  }
  return front_val;
}

int
peek_queue(Queue* queue) {
  assert (queue->front != -1);
  return queue->arr[queue->front];
}

void
free_queue(Queue* queue) {
  free(queue->arr);
  free(queue);
}
