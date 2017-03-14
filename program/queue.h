/* * * * * * *
 * Module for creating and manipulating stacks
 *
 * created for COMP20007 Design of Algorithms - Assignment 1, 2017
 * by Liam Aharon <laharon@student.unimelb.edu.au>
 */

typedef struct queue Queue;

struct queue {
  int front;
  int rear;
  int size;
  int maxn;
  int empty;
  int* arr;
};

Queue* new_queue(int maxn);

void enqueue_queue(Queue* queue, int num);

int dequeue_queue(Queue* queue);

int peek_queue(Queue* queue);
