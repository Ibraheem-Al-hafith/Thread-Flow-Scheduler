#include "../include/project.h"

pthread_mutex_t dWaker;
pthread_mutex_t completed_mutex;
void *unit_0(void *uq)
{
    UnitQueue *u = (UnitQueue *)uq;
    while (1)
    {
        Task *t = dequeue_unit(u); // fetching the task from the queue
        if (t == NULL)
        {
            break;
        }
        long long temp = t->value; // store the value in temp to avoid more memory access
        /*
            we use the next equation to fix negative values (if any) before execute
            the unit operation
            1. temp % M give us the negative value
            2. + M return the value to positive
            3. get the mod and the final result

            for example, temp = -3 & M = 10
            -3 % 10 = -3 which is wrong
            ((-3 % 10) + 10) % 10 = (-3 + 10) % 10
            = 7 % 10 = 7 which is the correct answer !
        */
        temp = ((temp % M) + M) % M;
        temp = (temp + 7) % M; // execute the unit operation
        t->value = temp;       // update the task value
        t->current_step++;     // increment the current step by one
        // printf("current step of task[%d] is {%d} out of {%d}\n", t->id, t->current_step, t->unit_count);
        //  check if the task is completed or not
        if (t->current_step < t->unit_count)
        {
            enqueue(wQueue, t); // insert the task again into the waiting queue
            usleep(500000);
        }
        else
        {
            // calculate the time it tooks until it finished
            // get the time
            clock_gettime(CLOCK_MONOTONIC, &t->dtime);
            /*
                the first operand to calculate the seconds, the second for the nanoseconds, the third
                to divide by 1 billion to adjust the summation
            */
            t->execution_time = (t->dtime.tv_sec - t->atime.tv_sec) + (t->dtime.tv_nsec - t->atime.tv_nsec) / 1e9;
            // display a message to indicate the end of the task
            printf("task[%d]: result = {%lld}, elapsed time is {%.9f} seconds\n", t->id, t->value, t->execution_time);
            pthread_mutex_lock(&completed_mutex);
            // increment completed_tasks by one
            completed_tasks++;
            pthread_mutex_unlock(&completed_mutex);
            usleep(500000); // make the thread sleeps for 500,000 microseconds = 0.5 seconds
        }
    }
    if (!dispatcher_status)
    {
        dispatcher_waker();
    }
    printf("unit[%d] has no tasks, now it is exiting !\n", u->unit_id);
    pthread_exit(NULL);
}
void *unit_1(void *uq)
{
    UnitQueue *u = (UnitQueue *)uq;
    while (!(receptor_done == true && total_tasks == completed_tasks))
    {
        Task *t = dequeue_unit(u); // fetching the task from the queue
        if (t == NULL)
        {
            break;
        }
        long long temp = t->value; // store the value in temp to avoid more memory access
        /*
            we use the next equation to fix negative values (if any) before execute
            the unit operation
            1. temp % M give us the negative value
            2. + M return the value to positive
            3. get the mod and the final result

            for example, temp = -3 & M = 10
            -3 % 10 = -3 which is wrong
            ((-3 % 10) + 10) % 10 = (-3 + 10) % 10
            = 7 % 10 = 7 which is the correct answer !
        */
        temp = ((temp % M) + M) % M;
        temp = (temp * 2) % M; // execute the unit operation
        t->value = temp;       // update the task value
        t->current_step++;     // increment the current step by one
        // printf("current step of task[%d] is {%d} out of {%d}\n", t->id, t->current_step, t->unit_count);
        //  check if the task is completed or not
        if (t->current_step < t->unit_count)
        {
            enqueue(wQueue, t); // insert the task again into the waiting queue
            usleep(500000);
        }
        else
        {
            // calculate the time it tooks until it finished
            // get the time
            clock_gettime(CLOCK_MONOTONIC, &t->dtime);
            /*
                the first operand to calculate the seconds, the second for the nanoseconds, the third
                to divide by 1 billion to adjust the summation
            */
            t->execution_time = (t->dtime.tv_sec - t->atime.tv_sec) + (t->dtime.tv_nsec - t->atime.tv_nsec) / 1e9;
            // display a message to indicate the end of the task
            printf("task[%d]: result = {%lld}, elapsed time is {%.9f} seconds\n", t->id, t->value, t->execution_time);
            pthread_mutex_lock(&completed_mutex);
            // increment completed_tasks by one
            completed_tasks++;
            pthread_mutex_unlock(&completed_mutex);
            usleep(500000); // make the thread sleeps for 500,000 microseconds = 0.5 seconds
        }
    }
    if (!dispatcher_status)
    {
        dispatcher_waker();
    }
    printf("unit[%d] has no tasks, now it is exiting !\n", u->unit_id);
    pthread_exit(NULL);
}
long long power(long long base, int power)
{
    long long result = 1;
    for (int i = 0; i < power; i++)
    {
        result *= base;
    }
    return result;
}
void *unit_2(void *uq)
{
    UnitQueue *u = (UnitQueue *)uq;
    while (!(receptor_done == true && total_tasks == completed_tasks))
    {
        Task *t = dequeue_unit(u); // fetching the task from the queue
        if (t == NULL)
        {
            break;
        }
        long long temp = t->value; // store the value in temp to avoid more memory access
        /*
            we use the next equation to fix negative values (if any) before execute
            the unit operation
            1. temp % M give us the negative value
            2. + M return the value to positive
            3. get the mod and the final result

            for example, temp = -3 & M = 10
            -3 % 10 = -3 which is wrong
            ((-3 % 10) + 10) % 10 = (-3 + 10) % 10
            = 7 % 10 = 7 which is the correct answer !
        */
        temp = ((temp % M) + M) % M;
        temp = power(temp, 5); // execute the unit operation
        temp = temp % M;
        t->value = temp;   // update the task value
        t->current_step++; // increment the current step by one
        // printf("current step of task[%d] is {%d} out of {%d}\n", t->id, t->current_step, t->unit_count);
        //  check if the task is completed or not
        if (t->current_step < t->unit_count)
        {
            enqueue(wQueue, t); // insert the task again into the waiting queue
            usleep(500000);
        }
        else
        {
            // calculate the time it tooks until it finished
            // get the time
            clock_gettime(CLOCK_MONOTONIC, &t->dtime);
            /*
                the first operand to calculate the seconds, the second for the nanoseconds, the third
                to divide by 1 billion to adjust the summation
            */
            t->execution_time = (t->dtime.tv_sec - t->atime.tv_sec) + (t->dtime.tv_nsec - t->atime.tv_nsec) / 1e9;
            // display a message to indicate the end of the task
            printf("task[%d]: result = {%lld}, elapsed time is {%.9f} seconds\n", t->id, t->value, t->execution_time);
            pthread_mutex_lock(&completed_mutex);
            // increment completed_tasks by one
            completed_tasks++;
            pthread_mutex_unlock(&completed_mutex);
            usleep(500000); // make the thread sleeps for 500,000 microseconds = 0.5 seconds
        }
    }
    if (!dispatcher_status)
    {
        dispatcher_waker();
    }
    printf("unit[%d] has no tasks, now it is exiting !\n", u->unit_id);
    pthread_exit(NULL);
}
void *unit_3(void *uq)
{
    UnitQueue *u = (UnitQueue *)uq;
    while (!(receptor_done == true && total_tasks == completed_tasks))
    {
        Task *t = dequeue_unit(u); // fetching the task from the queue
        if (t == NULL)
        {
            break;
        }
        long long temp = t->value; // store the value in temp to avoid more memory access
        /*
            we use the next equation to fix negative values (if any) before execute
            the unit operation
            1. temp % M give us the negative value
            2. + M return the value to positive
            3. get the mod and the final result

            for example, temp = -3 & M = 10
            -3 % 10 = -3 which is wrong
            ((-3 % 10) + 10) % 10 = (-3 + 10) % 10
            = 7 % 10 = 7 which is the correct answer !
        */
        temp = ((temp % M) + M) % M;
        temp = (temp - 19); // execute the unit operation
        t->value = temp;    // update the task value
        t->current_step++;  // increment the current step by one
        // printf("current step of task[%d] is {%d} out of {%d}\n", t->id, t->current_step, t->unit_count);
        //  check if the task is completed or not
        if (t->current_step < t->unit_count)
        {
            enqueue(wQueue, t); // insert the task again into the waiting queue
            usleep(500000);
        }
        else
        {
            // calculate the time it tooks until it finished
            // get the time
            clock_gettime(CLOCK_MONOTONIC, &t->dtime);
            /*
                the first operand to calculate the seconds, the second for the nanoseconds, the third
                to divide by 1 billion to adjust the summation
            */
            t->execution_time = (t->dtime.tv_sec - t->atime.tv_sec) + (t->dtime.tv_nsec - t->atime.tv_nsec) / 1e9;
            // display a message to indicate the end of the task
            printf("task[%d]: result = {%lld}, elapsed time is {%.9f} seconds\n", t->id, t->value, t->execution_time);
            pthread_mutex_lock(&completed_mutex);
            // increment completed_tasks by one
            completed_tasks++;
            pthread_mutex_unlock(&completed_mutex);
            usleep(500000); // make the thread sleeps for 500,000 microseconds = 0.5 seconds
        }
    }
    if (!dispatcher_status)
    {
        dispatcher_waker();
    }
    printf("unit[%d] has no tasks, now it is exiting !\n", u->unit_id);
    pthread_exit(NULL);
}
void *unit_4(void *uq)
{
    UnitQueue *u = (UnitQueue *)uq;
    while (!(receptor_done == true && total_tasks == completed_tasks))
    {
        Task *t = dequeue_unit(u); // fetching the task from the queue
        if (t == NULL)
        {
            break;
        }
        // display a message to indicate the end of the task
        printf("the value of the task[%d] after being processed is {%lld}\n", t->id, t->value);
        t->current_step++; // increment the current step by one
        // printf("current step of task[%d] is {%d} out of {%d}\n", t->id, t->current_step, t->unit_count);
        //  check if the task is completed or not
        if (t->current_step < t->unit_count)
        {
            enqueue(wQueue, t); // insert the task again into the waiting queue
            usleep(500000);
        }
        else
        {
            // calculate the time it tooks until it finished
            // get the time
            clock_gettime(CLOCK_MONOTONIC, &t->dtime);
            /*
                the first operand to calculate the seconds, the second for the nanoseconds, the third
                to divide by 1 billion to adjust the summation
            */
            t->execution_time = (t->dtime.tv_sec - t->atime.tv_sec) + (t->dtime.tv_nsec - t->atime.tv_nsec) / 1e9;
            // display a message to indicate the end of the task
            printf("task[%d]: result = {%lld}, elapsed time is {%.9f} seconds\n", t->id, t->value, t->execution_time);
            pthread_mutex_lock(&completed_mutex);
            // increment completed_tasks by one
            completed_tasks++;
            pthread_mutex_unlock(&completed_mutex);
            usleep(500000); // make the thread sleeps for 500,000 microseconds = 0.5 seconds
        }
    }
    if (!dispatcher_status)
    {
        dispatcher_waker();
    }
    printf("unit[%d] has no tasks, now it is exiting !\n", u->unit_id);
    pthread_exit(NULL);
}