#ifndef PROJECT_H
#define PROJECT_H

#define _POSIX_C_SOURCE 199309L // for clock_gettime function
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <stdbool.h>

#define M 10000                // The constant for modulo operations
#define QUEUE_CAPACITY 128     // identify the waiting queue capacity
#define UNIT_QUEUE_CAPACITY 32 // identify the unit queue capacity
#define UNITS_NUMBER 5

typedef struct
{
    /* The Global structure for the tasks */
    int id;                // Unique ID
    long long value;       // Value to be operated on
    struct timespec atime; // Arrival time
    struct timespec dtime; // dispature time
    double execution_time; // the time it took to complete
    int unit_count;        // How many units to be visit
    int *unit_ids;         // List of unit IDs
    int current_step;      // We add this to track the progress !!
} Task;

// The global structure for the completed tasks
typedef struct
{
    int id;                // unique ID
    long long value;       // value of the task
    double execution_time; // execution time
    int unit_count;        // number of visitied unit(s)
} Completed_task;

// The Queue structure
typedef struct
{
    Task *buffer[QUEUE_CAPACITY]; // size of the queue
    int rear;                     // point to the next free space
    int front;                    // points to the first element exists in the array
    int size;                     // number of elements in the array

    pthread_mutex_t mutex;    // to handle the synchronization between receptor and dispatcher
    pthread_cond_t not_full;  // to check if the queue is full
    pthread_cond_t not_empty; // to check if the queue is empty
} WaitingQueue;

extern WaitingQueue *wQueue; // Create an object for waiting queueto be used in the files
// The unit queue structure
typedef struct
{
    int unit_id;                       // the unit identifier
    Task *buffer[UNIT_QUEUE_CAPACITY]; // size of the queue
    int rear;                          // point to the next free space
    int front;                         // points to the first element exists in the array
    int size;                          // number of elements in the array

    pthread_mutex_t mutex;    // to handle the synchronization between dispatcher and unit
    pthread_cond_t not_full;  // to check if the queue is full
    pthread_cond_t not_empty; // to check if the queue is empty
} UnitQueue;
// create queue for each unit
extern UnitQueue *uQueue[UNITS_NUMBER];

// Function prototypes :
void queue_init(WaitingQueue *q);         // Queue initialization (for the waining queue)
void unit_queue_init(UnitQueue *u);       // unit queue initialization (for the unit queues)
void enqueue(WaitingQueue *q, Task *t);   // Inserting into queue
Task *dequeue(WaitingQueue *q);           // Extracting from the queue
void enqueue_unit(UnitQueue *u, Task *t); // a function used by dispatcher to enqueue into unit queue
Task *dequeue_unit(UnitQueue *u);         // a function used by the desired unit to operate on the task
void *receptor(void *arg);                // a function used for the receptor
void *dispatcher(void *q);                // a function used for the dispatcher
// declare the unit functions
void *unit_0(void *u);
void *unit_1(void *u);
void *unit_2(void *u);
void *unit_3(void *u);
void *unit_4(void *u);
// declare a function to wake up the waiting threads
void dispatcher_waker();
// declare a boolean array to check if the units has been waked
extern bool dispatcher_status;
// declare an integer that will be used as an indicator to receptor ending
extern bool receptor_done;
// declare an integer to count the number of tasks
extern int total_tasks;
// declare an integer to count the number of completed tasks
extern int completed_tasks;
// declare an rray for the completed task for the output file
extern Completed_task *ct;
// declare an integer for the capacity of the completed tasks array (initial capacity is 128)
extern int capacity;
// declare an integer to count the number of tasks inserted into the task array used for the output
extern int num_tasks;

/*

discreption:
Notice that inserting a task into queue takes the specific queue to insert on and a task to be inserted, and returns nothing
and notice that extracting a task from the queue returns a task

*/

#endif