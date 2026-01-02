/*
    In this file, several functions are defined and used
    for initialize the unit queues, enqueue tasks, and dequeue tasks
*/
#include "../include/project.h"

void unit_queue_init(UnitQueue *u)
{
    u->front = 0; // start from zero
    u->rear = 0;  // start from zero
    u->size = 0;  // make the queue empty
    // initalize all pointers to NULL
    for (int i = 0; i < UNIT_QUEUE_CAPACITY; i++)
    {
        u->buffer[i] = NULL;
    }
    // initalize the mutex and condition variables
    pthread_mutex_init(&u->mutex, NULL);
    pthread_cond_init(&u->not_empty, NULL);
    pthread_cond_init(&u->not_full, NULL);
}

void enqueue_unit(UnitQueue *u, Task *t)
{
    // lock the mutex to avoid problems such as changing in waiting queue in the same time between dispatcher and units
    pthread_mutex_lock(&u->mutex);
    // check whether the queue is empty or not
    if (u->size >= UNIT_QUEUE_CAPACITY)
    {
        // if so, waiting until a signal is made by the dequeue
        printf("The unit queue [%d] is full ! waiting until a room is available. \n", u->unit_id);
        // wait for the signal
        pthread_cond_wait(&u->not_full, &u->mutex);
    }
    // inserting the desired task
    u->buffer[u->rear] = t;
    // increment the rear by one
    // using module to enable wrapping
    u->rear = (u->rear + 1) % UNIT_QUEUE_CAPACITY;
    // increment the size by one
    u->size++;
    pthread_cond_signal(&u->not_empty);
    // unlock the mutex
    pthread_mutex_unlock(&u->mutex);
}

Task *dequeue_unit(UnitQueue *u)
{
    // declare a Task object
    Task *t;
    // lock the mutex to avoid problems such as changing in waiting queue in the same time between dispatcher and units
    pthread_mutex_lock(&u->mutex);
    // check whether the tasks have been proccessed
    if (receptor_done && total_tasks == completed_tasks && u->size == 0)
    {
        // unlock the mutex and return NULL
        pthread_mutex_unlock(&u->mutex);
        return NULL;
    }
    // check whether the queue is empty
    if (u->size == 0)
    {
        pthread_cond_wait(&u->not_empty, &u->mutex);
        /* sometimes the signal is sent from the dispatcher to indicate the finishing of all tasks
            so we need to check again
        */
        if (receptor_done && total_tasks == completed_tasks && u->size == 0)
        {
            // unlock the mutex and return NULL
            pthread_mutex_unlock(&u->mutex);
            return NULL;
        }
    }
    // otherwise, get the attributes of the task in the front
    t = u->buffer[u->front];
    // let the dequeued task points to NULL
    u->buffer[u->front] = NULL;
    // use mod to enable wrapping
    u->front = (u->front + 1) % UNIT_QUEUE_CAPACITY;
    // decrement size by one
    u->size--;
    // signal to the dispatcher if it is waiting because the queue is full
    pthread_cond_signal(&u->not_full);
    // unlock the mutex
    pthread_mutex_unlock(&u->mutex);
    // return the task to the desired unit
    return t;
}