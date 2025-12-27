#include "project.h"

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
        printf("The queue is full ! waiting until a room is available. \n");
        // wait for the signal
        pthread_cond_wait(&q->not_full, &q->mutex);
    }
    /*
    We used clock_gettime() instead of gettimeofday() because it is more precisely in
    which it measures in nanoseconds, furthermore we used CLOCK_MONOTONIC because it
    gives the actual time and not affected to time changes such as NTP

    we assign the clock time in this step because the task can be wait if
    the dispatcher is using waiting queue
    */
    clock_gettime(CLOCK_MONOTONIC, &t->atime);
    // print a message to indicate of inserting a task
    printf("a room is available ! entering the data .. \n");
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
    Task *t;
    pthread_mutex_lock(&q->mutex);
    if (&q->size == 0)
    {
        printf("The queue is empty ! waiting until the queue is filled with data. \n");
        pthread_cond_wait(&q->not_empty, &q->mutex);
    }
    t = q->buffer[q->front];
    q->buffer[q->front] = NULL;
    q->front = (q->front + 1) % QUEUE_CAPACITY;
    q->size--;
    pthread_cond_signal(&q->not_full);
    pthread_mutex_unlock(&q->mutex);
    return t;
}