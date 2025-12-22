#ifndef PROJECT_H
#define PROJECT_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

#define M 10000 //The constant for modulo operations

typedef struct {
    /* The Global structure for the tasks */
    int id;                 // Unique ID
    int value;              // Value to be operated on
    struct timeval atime;   // Arrival time
    int unit_count;         // How many units to be visit
    int *unit_id;           // List of unit IDs
    int current_step;       // We add this to track the progress !!
} Task;

// The Node for our linked-list queue
typedef struct Node {
    Task *task;
    struct Node *next;
} Node;

// The Queue structure
typedef struct {
    Node *head;
    Node *tail;
    pthread_mutex_t lock;   // This is the "key" to the queue, this prevents two objects from accessing the queue on the same time
    pthread_cond_t notify;  // This is the "Alarm clock" for waiting thread , think of it like when the queue is empty, then the dispatcher is sleeping, the moment the input insert into the queue, it will notify the dispatcher to start the work
} Queue;

// Function prototypes :
void queue_init(Queue *q);          // Queue initialization (for the waining queue and unit queues)
void enqueue(Queue *q, Task *t);    // Inserting into queue
Task* dequeue(Queue *q);           // Extracting from the queue
/*

discribtion:
Notice that inserting a task into queue takes the specific queue to insert on and a task to be inserted, and returns nothing
and notice that extracting a task from the queue returns a task

*/

#endif