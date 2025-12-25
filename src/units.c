#include "../include/project.h"

void* unit_0(UnitQueue* u){
    pthread_mutex_lock(&u->mutex);  // lock the mutex to ensure safety between dispatcher and the unit
    // check whether the unit queue is empty or not
    if (u->size == 0){
        printf("Unit[0] queue is empty ! wait until it is filled. \n");    // display a message that the queue is empty
        pthread_cond_wait(&u->not_empty, &u->mutex);    // wait a signal from the dispatcher
    }
    Task* t = dequeue_unit(u);  // fetching the task from the queue
    int temp = t-> value;   // store the value in temp to avoid more memory access
    temp = (temp + 7) % M;  // execute the unit operation
    t-> value = temp;   // update the task value
    t->current_step++;  // increment the current step by one
    // check if the task is completed or not
    if (t->current_step < t-> unit_count){
        enqueue(wQueue, t); // insert the task again into the waiting queue
    }
    else 
        // display a message to indicate the end of the task
        printf("the task[%d] has been finished successfully and the value is {%d}\n", t->id, t->value);
    pthread_cond_signal(&u->not_full);  // send a signal to the dispatcher to indicate the availability of a room
    pthread_mutex_unlock(&u->mutex);    // unlock the mutex for the dispatcher
    usleep(500000);   // make the thread sleeps for 500,000 microseconds = 0.5 seconds
}
void* unit_1(UnitQueue* u){
    pthread_mutex_lock(&u->mutex);  // lock the mutex to ensure safety between dispatcher and the unit
    // check whether the unit queue is empty or not
    if (u->size == 0){
        printf("Unit[1] queue is empty ! wait until it is filled. \n");    // display a message that the queue is empty
        pthread_cond_wait(&u->not_empty, &u->mutex);    // wait a signal from the dispatcher
    }
    Task* t = dequeue_unit(u);  // fetching the task from the queue
    int temp = t-> value;   // store the value in temp to avoid more memory access
    temp = (temp * 2) % M;  // execute the unit operation
    t-> value = temp;   // update the task value
    t->current_step++;  // increment the current step by one
    // check if the task is completed or not
    if (t->current_step < t-> unit_count){
        enqueue(wQueue, t); // insert the task again into the waiting queue
    }
    else 
        // display a message to indicate the end of the task
        printf("the task[%d] has been finished successfully and the value is {%d}\n", t->id, t->value);
    pthread_cond_signal(&u->not_full);  // send a signal to the dispatcher to indicate the availability of a room
    pthread_mutex_unlock(&u->mutex);    // unlock the mutex for the dispatcher
    usleep(500000);   // make the thread sleeps for 500,000 microseconds = 0.5 seconds
}
void* unit_2(UnitQueue* u){
    pthread_mutex_lock(&u->mutex);  // lock the mutex to ensure safety between dispatcher and the unit
    // check whether the unit queue is empty or not
    if (u->size == 0){
        printf("Unit[2] queue is empty ! wait until it is filled. \n");    // display a message that the queue is empty
        pthread_cond_wait(&u->not_empty, &u->mutex);    // wait a signal from the dispatcher
    }
    Task* t = dequeue_unit(u);  // fetching the task from the queue
    int temp = t-> value;   // store the value in temp to avoid more memory access
    temp = (temp ^ 5) % M;  // execute the unit operation
    t-> value = temp;   // update the task value
    t->current_step++;  // increment the current step by one
    // check if the task is completed or not
    if (t->current_step < t-> unit_count){
        enqueue(wQueue, t); // insert the task again into the waiting queue
    }
    else 
        // display a message to indicate the end of the task
        printf("the task[%d] has been finished successfully and the value is {%d}\n", t->id, t->value);
    pthread_cond_signal(&u->not_full);  // send a signal to the dispatcher to indicate the availability of a room
    pthread_mutex_unlock(&u->mutex);    // unlock the mutex for the dispatcher
    usleep(500000);   // make the thread sleeps for 500,000 microseconds = 0.5 seconds
}
void* unit_3(UnitQueue* u){
    pthread_mutex_lock(&u->mutex);  // lock the mutex to ensure safety between dispatcher and the unit
    // check whether the unit queue is empty or not
    if (u->size == 0){
        printf("Unit[3] queue is empty ! wait until it is filled. \n");    // display a message that the queue is empty
        pthread_cond_wait(&u->not_empty, &u->mutex);    // wait a signal from the dispatcher
    }
    Task* t = dequeue_unit(u);  // fetching the task from the queue
    int temp = t-> value;   // store the value in temp to avoid more memory access
    temp = (temp - 19) ;  // execute the unit operation
    t-> value = temp;   // update the task value
    t->current_step++;  // increment the current step by one
    // check if the task is completed or not
    if (t->current_step < t-> unit_count){
        enqueue(wQueue, t); // insert the task again into the waiting queue
    }
    else 
        // display a message to indicate the end of the task
        printf("the task[%d] has been finished successfully and the value is {%d}\n", t->id, t->value);
    pthread_cond_signal(&u->not_full);  // send a signal to the dispatcher to indicate the availability of a room
    pthread_mutex_unlock(&u->mutex);    // unlock the mutex for the dispatcher
    usleep(500000);   // make the thread sleeps for 500,000 microseconds = 0.5 seconds
}
void* unit_4(UnitQueue* u){
    pthread_mutex_lock(&u->mutex);  // lock the mutex to ensure safety between dispatcher and the unit
    // check whether the unit queue is empty or not
    if (u->size == 0){
        printf("Unit[4] queue is empty ! wait until it is filled. \n");    // display a message that the queue is empty
        pthread_cond_wait(&u->not_empty, &u->mutex);    // wait a signal from the dispatcher
    }
    Task* t = dequeue_unit(u);  // fetching the task from the queue
    // display a message to indicate the end of the task
    printf("the value of the task[%d] after being processed is {%d} ", t->id, t->value);
    // check if the task is completed or not
    if (t->current_step < t-> unit_count){
        enqueue(wQueue, t); // insert the task again into the waiting queue
    }
    else 
        // display a message to indicate the end of the task
        printf("the task[%d] has been finished successfully and the value is {%d}\n", t->id, t->value);
    pthread_cond_signal(&u->not_full);  // send a signal to the dispatcher to indicate the availability of a room
    pthread_mutex_unlock(&u->mutex);    // unlock the mutex for the dispatcher
    usleep(500000);   // make the thread sleeps for 500,000 microseconds = 0.5 seconds
}