#ifndef PROJECT_H
#define PROJECT_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

#define M 10000 //The constant for modulo operations
#define QUEUE_CAPACITY 100  // identify the waiting queue capacity
#define UNIT_QUEUE_CAPACITY 20  // identify the unit queue capacity

typedef struct {
    /* The Global structure for the tasks */
    int id;                 // Unique ID
    int value;              // Value to be operated on
    struct timeval atime;   // Arrival time
    int unit_count;         // How many units to be visit
    int *unit_id;           // List of unit IDs
    int current_step;       // We add this to track the progress !!
} Task;
// The Queue structure
typedef struct {
    struct task* buffer[100]; // size of the queue
    int rear;   // point to the next free space
    int front;  // points to the first element exists in the array
    int size;   // number of elements in the array

    pthread_mutex_t mutex;  // to handle the synchronization between receptor and dispatcher
    pthread_cond_t not_full;    // to check if the queue is full
    pthread_cond_t not_empty;   // to check if the queue is empty
}WaitingQueue;

WaitingQueue* wQueue;   // Create an object for waiting queueto be used in the files
// The unit queue structure
typedef struct {
    struct task* buffer[20]; // size of the queue
    int rear;   // point to the next free space
    int front;  // points to the first element exists in the array
    int size;   // number of elements in the array

    pthread_mutex_t mutex;  // to handle the synchronization between dispatcher and unit
    pthread_cond_t not_full;    // to check if the queue is full
    pthread_cond_t not_empty;   // to check if the queue is empty
}UnitQueue;


// Function prototypes :
void queue_init(WaitingQueue *q);          // Queue initialization (for the waining queue and unit queues)
void enqueue(WaitingQueue *q, Task *t);    // Inserting into queue
Task* dequeue(WaitingQueue *q);           // Extracting from the queue
/*

discribtion:
Notice that inserting a task into queue takes the specific queue to insert on and a task to be inserted, and returns nothing
and notice that extracting a task from the queue returns a task

*/

#endif