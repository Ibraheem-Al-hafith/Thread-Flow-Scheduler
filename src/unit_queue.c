#include "../include/project.h"

void unit_queue_init(UnitQueue* u){
    u->front = 0;   // start from zero
    u->rear = 0;    // start from zero
    u->size = 0;    // make the queue empty
    // initalize all pointers to NULL
    for (int i = 0; i < UNIT_QUEUE_CAPACITY; i++){
        u->buffer[i] = NULL;
    }
    // initalize the mutex and condition variables
    pthread_mutex_init(&u->mutex, NULL);
    pthread_cond_init(&u->not_empty, NULL);
    pthread_cond_init(&u->not_full, NULL);
}

void enqueue_unit(UnitQueue* u,Task* t){
    pthread_mutex_lock(&u->mutex);   // lock the mutex to avoid conflict
    // check whether the queue is empty or not 
    if (u->size >= UNIT_QUEUE_CAPACITY){
        // if so, waiting until a signal is made by the dequeue
        printf("The queue is full ! waiting until a room is available. \n");
        // wait for the signal
        pthread_cond_wait(&u->not_full, &u->mutex);
    }
    // print a message to indicate of inserting a task
    printf("a room is available ! entering the data .. \n");
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

Task* dequeue_unit(UnitQueue* u){
    Task* t;
    pthread_mutex_lock(&u->mutex);
    if (&u->size == 0){
        printf("The queue is empty ! waiting until the queue is filled with data. \n");
        pthread_cond_wait(&u->not_empty, &u->mutex);
    }
    t = u->buffer[u->front];
    u->buffer[u->front] = NULL;
    u->front = (u->front + 1) % UNIT_QUEUE_CAPACITY;
    u->size--;
    pthread_cond_signal(&u->not_full);
    pthread_mutex_unlock(&u->mutex);
    return t;
}