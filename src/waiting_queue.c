/*
    In this file, several functions are defined and used
    for initialize the waiting queue, enqueue tasks, and dequeue tasks
*/

#include "../include/project.h"

void queue_init(WaitingQueue *q)
{
    q->front = 0; // start from zero
    q->rear = 0;  // start from zero
    q->size = 0;  // make the queue empty
    // initalize all pointers to NULL
    for (int i = 0; i < QUEUE_CAPACITY; i++)
    {
        q->buffer[i] = NULL;
    }
    // initalize the mutex and condition variables
    pthread_mutex_init(&q->mutex, NULL);
    pthread_cond_init(&q->not_empty, NULL);
    pthread_cond_init(&q->not_full, NULL);
}

void enqueue(WaitingQueue *q, Task *t)
{
    pthread_mutex_lock(&q->mutex); // lock the mutex to avoid conflict
    // check whether the queue is empty or not
    if (q->size >= QUEUE_CAPACITY)
    {
        // if so, waiting until a signal is made by the dequeue
        printf("The waiting queue is full ! waiting until a room is available. \n");
        // wait for the signal
        pthread_cond_wait(&q->not_full, &q->mutex);
    }
    /*
        if this is the first time the task is being insert to the queue
        we get the current time and initialize it to the task, otherwise we avoid
        it because this is not the first time it enters the queue (has more than one unit to visit)
    */
    if (t->atime.tv_sec == 0 && t->atime.tv_sec == 0)
    {
        /*
            We used clock_gettime() instead of gettimeofday() because it is more precisely in
            which it measures in nanoseconds, furthermore we used CLOCK_MONOTONIC because it
            gives the actual time and not affected to time changes such as NTP

            we assign the clock time in this step because the task can be wait if
            the dispatcher is using waiting queue
        */
        clock_gettime(CLOCK_MONOTONIC, &t->atime);
    }
    // inserting the desired task
    q->buffer[q->rear] = t;
    // increment the rear by one
    // using module to enable wrapping
    q->rear = (q->rear + 1) % QUEUE_CAPACITY;
    // increment the size by one
    q->size++;
    pthread_cond_signal(&q->not_empty);
    // unlock the mutex
    pthread_mutex_unlock(&q->mutex);
}

Task *dequeue(WaitingQueue *q)
{
    // declare a Task object
    Task *t;
    // lock the mutex to avoid changing in the same time between receptor and dispatcher
    pthread_mutex_lock(&q->mutex);
    // check whether the program has finished
    if (receptor_done && total_tasks == completed_tasks && q->size == 0)
    {
        // unlock the mutex and return NULL to notify the dispatcher
        pthread_mutex_unlock(&q->mutex);
        return NULL;
    }
    // check whether the queue is empty, if so,  wait until it is filled by the receptor
    if (q->size == 0)
    {
        pthread_cond_wait(&q->not_empty, &q->mutex);
        /*
            sometimes the signal is sent by one of the units to notify the end of the program
            so we need to check again if the program has finished or not
        */
        if (receptor_done && total_tasks == completed_tasks && q->size == 0)
        {
            // unlock the mutex and return NULL to notify the dispatcher
            pthread_mutex_unlock(&q->mutex);
            return NULL;
        }
    }
    // otherwise, all the task attributes is assigned from the task in the front of the waiting queue
    t = q->buffer[q->front];
    // let the room in the front point to NULL
    q->buffer[q->front] = NULL;
    // enable wrapping if the queue has reach its size
    q->front = (q->front + 1) % QUEUE_CAPACITY;
    // decrement the size by one
    q->size--;
    // signal the receptor and notify it by availability of room(s)
    pthread_cond_signal(&q->not_full);
    // unlock the mutex
    pthread_mutex_unlock(&q->mutex);
    return t;
}