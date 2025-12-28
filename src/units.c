#include "../include/project.h"
void *unit_0(void *uq)
{
    UnitQueue *u = (UnitQueue *)uq;
    while (!(receptor_done == true && u->rear == 0 && u->front == 0))
    {
        Task *t = dequeue_unit(u); // fetching the task from the queue
        int temp = t->value;       // store the value in temp to avoid more memory access
        temp = (temp + 7) % M;     // execute the unit operation
        t->value = temp;           // update the task value
        t->current_step++;         // increment the current step by one
        printf("current step of task[%d] is {%d} out of {%d}\n", t->id, t->current_step, t->unit_count);
        // check if the task is completed or not
        if (t->current_step < t->unit_count)
        {
            enqueue(wQueue, t); // insert the task again into the waiting queue
            usleep(500000);
        }
        else
        {
            // calculate the time it tooks until it finished
            // get the time
            // clock_gettime(CLOCK_MONOTONIC, &t->dtime);
            /*
                the first operand to calculate the seconds, the second for the nanoseconds, the third
                to divide by 1 billion to adjust the summation
            */
            t->execution_time = (t->dtime.tv_sec - t->atime.tv_sec) + (t->dtime.tv_usec - t->atime.tv_usec) / 1e9;
            // display a message to indicate the end of the task
            printf("the task[%d] has been finished successfully and it took {%d} seconds. The value is {%d}\n", t->id, t->execution_time, t->value);
            usleep(500000); // make the thread sleeps for 500,000 microseconds = 0.5 seconds
        }
    }
}
void *unit_1(void *uq)
{
    UnitQueue *u = (UnitQueue *)uq;
    while (!(receptor_done == true && u->rear == 0 && u->front == 0))
    {
        Task *t = dequeue_unit(u); // fetching the task from the queue
        int temp = t->value;       // store the value in temp to avoid more memory access
        temp = (temp * 2) % M;     // execute the unit operation
        t->value = temp;           // update the task value
        t->current_step++;         // increment the current step by one
        printf("current step of task[%d] is {%d} out of {%d}\n", t->id, t->current_step, t->unit_count);
        // check if the task is completed or not
        if (t->current_step < t->unit_count)
        {
            enqueue(wQueue, t); // insert the task again into the waiting queue
            usleep(500000);
        }
        else
        {
            // calculate the time it tooks until it finished
            // get the time
            // clock_gettime(CLOCK_MONOTONIC, &t->dtime);
            /*
                the first operand to calculate the seconds, the second for the nanoseconds, the third
                to divide by 1 billion to adjust the summation
            */
            t->execution_time = (t->dtime.tv_sec - t->atime.tv_sec) + (t->dtime.tv_usec - t->atime.tv_usec) / 1e9;
            // display a message to indicate the end of the task
            printf("the task[%d] has been finished successfully and it took {%d} seconds. The value is {%d}\n", t->id, t->execution_time, t->value);
            usleep(500000); // make the thread sleeps for 500,000 microseconds = 0.5 seconds
        }
    }
}
void *unit_2(void *uq)
{
    UnitQueue *u = (UnitQueue *)uq;
    while (!(receptor_done == true && u->rear == 0 && u->front == 0))
    {
        Task *t = dequeue_unit(u); // fetching the task from the queue
        int temp = t->value;       // store the value in temp to avoid more memory access
        temp = (temp ^ 5) % M;     // execute the unit operation
        t->value = temp;           // update the task value
        t->current_step++;         // increment the current step by one
        printf("current step of task[%d] is {%d} out of {%d}\n", t->id, t->current_step, t->unit_count);
        // check if the task is completed or not
        if (t->current_step < t->unit_count)
        {
            enqueue(wQueue, t); // insert the task again into the waiting queue
            usleep(500000);
        }
        else
        {
            // calculate the time it tooks until it finished
            // get the time
            // clock_gettime(CLOCK_MONOTONIC, &t->dtime);
            /*
                the first operand to calculate the seconds, the second for the nanoseconds, the third
                to divide by 1 billion to adjust the summation
            */
            t->execution_time = (t->dtime.tv_sec - t->atime.tv_sec) + (t->dtime.tv_usec - t->atime.tv_usec) / 1e9;
            // display a message to indicate the end of the task
            printf("the task[%d] has been finished successfully and it took {%d} seconds. The value is {%d}\n", t->id, t->execution_time, t->value);
            usleep(500000); // make the thread sleeps for 500,000 microseconds = 0.5 seconds
        }
    }
}
void *unit_3(void *uq)
{
    UnitQueue *u = (UnitQueue *)uq;
    while (!(receptor_done == true && u->rear == 0 && u->front == 0))
    {
        Task *t = dequeue_unit(u); // fetching the task from the queue
        int temp = t->value;       // store the value in temp to avoid more memory access
        temp = (temp - 19);        // execute the unit operation
        t->value = temp;           // update the task value
        t->current_step++;         // increment the current step by one
        printf("current step of task[%d] is {%d} out of {%d}\n", t->id, t->current_step, t->unit_count);
        // check if the task is completed or not
        if (t->current_step < t->unit_count)
        {
            enqueue(wQueue, t); // insert the task again into the waiting queue
            usleep(500000);
        }
        else
        {
            // calculate the time it tooks until it finished
            // get the time
            // clock_gettime(CLOCK_MONOTONIC, &t->dtime);
            /*
                the first operand to calculate the seconds, the second for the nanoseconds, the third
                to divide by 1 billion to adjust the summation
            */
            t->execution_time = (t->dtime.tv_sec - t->atime.tv_sec) + (t->dtime.tv_usec - t->atime.tv_usec) / 1e9;
            // display a message to indicate the end of the task
            printf("the task[%d] has been finished successfully and it took {%d} seconds. The value is {%d}\n", t->id, t->execution_time, t->value);
            usleep(500000); // make the thread sleeps for 500,000 microseconds = 0.5 seconds
        }
    }
}
void *unit_4(void *uq)
{
    UnitQueue *u = (UnitQueue *)uq;
    while (!(receptor_done == true && u->rear == 0 && u->front == 0))
    {
        Task *t = dequeue_unit(u); // fetching the task from the queue
        // display a message to indicate the end of the task
        printf("the value of the task[%d] after being processed is {%d}\n", t->id, t->value);
        t->current_step++; // increment the current step by one
        printf("current step of task[%d] is {%d} out of {%d}\n", t->id, t->current_step, t->unit_count);
        // check if the task is completed or not
        if (t->current_step < t->unit_count)
        {
            enqueue(wQueue, t); // insert the task again into the waiting queue
            usleep(500000);
        }
        else
        {
            // calculate the time it tooks until it finished
            // get the time
            // clock_gettime(CLOCK_MONOTONIC, &t->dtime);
            /*
                the first operand to calculate the seconds, the second for the nanoseconds, the third
                to divide by 1 billion to adjust the summation
            */
            t->execution_time = (t->dtime.tv_sec - t->atime.tv_sec) + (t->dtime.tv_usec - t->atime.tv_usec) / 1e9;
            // display a message to indicate the end of the task
            printf("the task[%d] has been finished successfully and it took {%d} seconds. The value is {%d}\n", t->id, t->execution_time, t->value);
            usleep(500000); // make the thread sleeps for 500,000 microseconds = 0.5 seconds
        }
    }
}