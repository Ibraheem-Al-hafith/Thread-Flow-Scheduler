#ifndef PROJECT_H
#define PROJECT_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>
#include <linux/time.h>

#define M 10000                // The constant for modulo operations
#define QUEUE_CAPACITY 128     // identify the waiting queue capacity
#define UNIT_QUEUE_CAPACITY 32 // identify the unit queue capacity
#define UNITS_NUMBER 5

typedef struct
{
    /* The Global structure for the tasks */
    int id;                // Unique ID
    int value;             // Value to be operated on
    struct timeval atime;  // Arrival time
    struct timeval dtime;  // dispature time
    double execution_time; // the time it took to complete
    int unit_count;        // How many units to be visit
    int *unit_ids;         // List of unit IDs
    int current_step;      // We add this to track the progress !!
} Task;

// The Queue structure
typedef struct
{
    struct task *buffer[QUEUE_CAPACITY]; // size of the queue
    int rear;                            // point to the next free space
    int front;                           // points to the first element exists in the array
    int size;                            // number of elements in the array

    pthread_mutex_t mutex;    // to handle the synchronization between receptor and dispatcher
    pthread_cond_t not_full;  // to check if the queue is full
    pthread_cond_t not_empty; // to check if the queue is empty
} WaitingQueue;

WaitingQueue *wQueue; // Create an object for waiting queueto be used in the files
// The unit queue structure
typedef struct
{
    struct task *buffer[UNIT_QUEUE_CAPACITY]; // size of the queue
    int rear;                                 // point to the next free space
    int front;                                // points to the first element exists in the array
    int size;                                 // number of elements in the array

    pthread_mutex_t mutex;    // to handle the synchronization between dispatcher and unit
    pthread_cond_t not_full;  // to check if the queue is full
    pthread_cond_t not_empty; // to check if the queue is empty
} UnitQueue;
// create queue for each unit
UnitQueue *uQueue[UNITS_NUMBER];

// Function prototypes :
void queue_init(WaitingQueue *q);         // Queue initialization (for the waining queue)
void unit_queue_init(UnitQueue *u);       // unit queue initialization (for the unit queues)
void enqueue(WaitingQueue *q, Task *t);   // Inserting into queue
Task *dequeue(WaitingQueue *q);           // Extracting from the queue
void enqueue_unit(UnitQueue *u, Task *t); // a function used by dispatcher to enqueue into unit queue
Task *dequeue_unit(UnitQueue *u);         // a function used by the desired unit to operate on the task
void *receptor(void *arg);                // a function used for the receptor
// define an integer that will be used as an indicator to receptor ending
int receptor_done = 0;
// define an integer to count the number of tasks
int total_tasks = 0;
void *dispatcher(WaitingQueue *q); // a function used for the dispatcher
// define the unit functions
void *unit_0(UnitQueue *u);
void *unit_1(UnitQueue *u);
void *unit_2(UnitQueue *u);
void *unit_3(UnitQueue *u);
void *unit_4(UnitQueue *u);

/*

discribtion:
Notice that inserting a task into queue takes the specific queue to insert on and a task to be inserted, and returns nothing
and notice that extracting a task from the queue returns a task

*/

#endif