#include "../include/project.h"

void* unit_0(UnitQueue* u){
    pthread_mutex_lock(&u->mutex);  // lock the mutex to ensure safety between dispatcher and the unit
    // check whether the unit queue is empty or not
    if (u->size == 0){
        printf("Unit queue is empty ! wait until it is filled. \n");    // display a message that the queue is empty
        pthread_cond_wait(&u->not_empty, &u->mutex);    // wait a signal from the dispatcher
    }
    Task* t = dequeue_unit(u);  // fetching the task from the queue
    int temp = t-> value;   // store the value in temp to avoid more memory access
    temp = (temp + 7) % M;  // execute the unit operation
    t-> value = temp;   // update the task value
    t->current_step++;  // increment the current step by one
    // check if the task is completed or not
    if (t->current_step < t-> unit_count){
        printf("The operation on the task[%d] has been completed. \n", t->id);  // display a message that the operation is done
        enqueue(wQueue, t); // insert the task again into the waiting queue
    }
    else 
        printf("the task[%d] has been finished successfully and the value is {%d}\n", t->id, t->value);
        // display a message to indicate the end of the task
}
void* unit_0(UnitQueue* u){
    pthread_mutex_lock(&u->mutex);  // lock the mutex to ensure safety between dispatcher and the unit
    // check whether the unit queue is empty or not
    if (u->size == 0){
        printf("Unit queue is empty ! wait until it is filled. \n");    // display a message that the queue is empty
        pthread_cond_wait(&u->not_empty, &u->mutex);    // wait a signal from the dispatcher
    }
    Task* t = dequeue_unit(u);  // fetching the task from the queue
    int temp = t-> value;   // store the value in temp to avoid more memory access
    temp = (temp + 7) % M;  // execute the unit operation
    t-> value = temp;   // update the task value
    t->current_step++;  // increment the current step by one
    // check if the task is completed or not
    if (t->current_step < t-> unit_count){
        printf("The operation on the task[%d] has been completed. \n", t->id);  // display a message that the operation is done
        enqueue(wQueue, t); // insert the task again into the waiting queue
    }
    else 
        printf("the task[%d] has been finished successfully and the value is {%d}\n", t->id, t->value);
        // display a message to indicate the end of the task
}
void* unit_0(UnitQueue* u){
    pthread_mutex_lock(&u->mutex);  // lock the mutex to ensure safety between dispatcher and the unit
    // check whether the unit queue is empty or not
    if (u->size == 0){
        printf("Unit queue is empty ! wait until it is filled. \n");    // display a message that the queue is empty
        pthread_cond_wait(&u->not_empty, &u->mutex);    // wait a signal from the dispatcher
    }
    Task* t = dequeue_unit(u);  // fetching the task from the queue
    int temp = t-> value;   // store the value in temp to avoid more memory access
    temp = (temp + 7) % M;  // execute the unit operation
    t-> value = temp;   // update the task value
    t->current_step++;  // increment the current step by one
    // check if the task is completed or not
    if (t->current_step < t-> unit_count){
        printf("The operation on the task[%d] has been completed. \n", t->id);  // display a message that the operation is done
        enqueue(wQueue, t); // insert the task again into the waiting queue
    }
    else 
        printf("the task[%d] has been finished successfully and the value is {%d}\n", t->id, t->value);
        // display a message to indicate the end of the task
}
void* unit_0(UnitQueue* u){
    pthread_mutex_lock(&u->mutex);  // lock the mutex to ensure safety between dispatcher and the unit
    // check whether the unit queue is empty or not
    if (u->size == 0){
        printf("Unit queue is empty ! wait until it is filled. \n");    // display a message that the queue is empty
        pthread_cond_wait(&u->not_empty, &u->mutex);    // wait a signal from the dispatcher
    }
    Task* t = dequeue_unit(u);  // fetching the task from the queue
    int temp = t-> value;   // store the value in temp to avoid more memory access
    temp = (temp + 7) % M;  // execute the unit operation
    t-> value = temp;   // update the task value
    t->current_step++;  // increment the current step by one
    // check if the task is completed or not
    if (t->current_step < t-> unit_count){
        printf("The operation on the task[%d] has been completed. \n", t->id);  // display a message that the operation is done
        enqueue(wQueue, t); // insert the task again into the waiting queue
    }
    else 
        printf("the task[%d] has been finished successfully and the value is {%d}\n", t->id, t->value);
        // display a message to indicate the end of the task
}
void* unit_0(UnitQueue* u){
    pthread_mutex_lock(&u->mutex);  // lock the mutex to ensure safety between dispatcher and the unit
    // check whether the unit queue is empty or not
    if (u->size == 0){
        printf("Unit queue is empty ! wait until it is filled. \n");    // display a message that the queue is empty
        pthread_cond_wait(&u->not_empty, &u->mutex);    // wait a signal from the dispatcher
    }
    Task* t = dequeue_unit(u);  // fetching the task from the queue
    int temp = t-> value;   // store the value in temp to avoid more memory access
    temp = (temp + 7) % M;  // execute the unit operation
    t-> value = temp;   // update the task value
    t->current_step++;  // increment the current step by one
    // check if the task is completed or not
    if (t->current_step < t-> unit_count){
        printf("The operation on the task[%d] has been completed. \n", t->id);  // display a message that the operation is done
        enqueue(wQueue, t); // insert the task again into the waiting queue
    }
    else 
        printf("the task[%d] has been finished successfully and the value is {%d}\n", t->id, t->value);
        // display a message to indicate the end of the task
}