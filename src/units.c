/*
    Units:
    Each unit recieves a pointer to its queue, then it dequeues the task in the front
    then it makes its operation and check if there is a need to send it back to the waiting
    queue or print a message of completing the task in question
*/
#include "../include/project.h"

// declare a mutex to avoid race conditions on completed_tasks variable
pthread_mutex_t completed_mutex;
// declare a mutex for the realloc
pthread_mutex_t realloc_mutex;
void *unit_0(void *uq)
{
    UnitQueue *u = (UnitQueue *)uq;
    while (!(receptor_done == true && total_tasks == completed_tasks))
    {
        Task *t = dequeue_unit(u); // fetching the task from the queue
        // check whether the t is NULL which indicate the end of all tasks
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
            // make th thread sleep for 50,000 microseconds = 0.5 seconds
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
            pthread_mutex_lock(&realloc_mutex);
            if (capacity < t->id)
            {
                while (capacity < t->id)
                {
                    capacity *= 2;
                }
                Completed_task *tmp = realloc(ct, capacity * sizeof(Completed_task));
                if (!tmp)
                {
                    pthread_mutex_unlock(&realloc_mutex);
                    perror("realloc failed\n");
                    exit(1);
                }
                ct = tmp;
            }
            Completed_task c0;
            // assign the attributes of completed task to the other task object to handle output
            c0.id = t->id;
            c0.value = t->value;
            c0.unit_count = t->unit_count;
            c0.execution_time = t->execution_time;
            ct[c0.id] = c0;
            num_tasks++;
            pthread_mutex_unlock(&realloc_mutex);
            pthread_mutex_lock(&completed_mutex);
            // increment completed_tasks by one
            completed_tasks++;
            pthread_mutex_unlock(&completed_mutex);
            usleep(500000); // make the thread sleep for 500,000 microseconds = 0.5 seconds
        }
    }
    /*
        If one unit notifies that the program has executed all the tasks, it will wake
        the dispatcher and by its turn, it will wake the uninformed units

        sometimes more than one units got notified, so by using dispatcher_status
        we can avoid losting dispatcher_waker
    */
    if (!dispatcher_status)
    {
        dispatcher_waker();
    }
    // print indicating message that the unit has finished its job
    printf("unit[%d] has no tasks, now it is exiting !\n", u->unit_id);
    // exit the thread
    pthread_exit(NULL);
}
void *unit_1(void *uq)
{
    UnitQueue *u = (UnitQueue *)uq;
    // loop until all the tasks have been read by the receptor and completed by the units
    while (!(receptor_done == true && total_tasks == completed_tasks))
    {
        Task *t = dequeue_unit(u); // fetching the task from the queue
        // check whether the t is NULL which indicate the end of all tasks
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
            // make th thread sleep for 50,000 microseconds = 0.5 seconds
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
            pthread_mutex_lock(&realloc_mutex);
            if (capacity < t->id)
            {
                while (capacity < t->id)
                {
                    capacity *= 2;
                }
                Completed_task *tmp = realloc(ct, capacity * sizeof(Completed_task));
                if (!tmp)
                {
                    pthread_mutex_unlock(&realloc_mutex);
                    perror("realloc failed\n");
                    exit(1);
                }
                ct = tmp;
            }
            Completed_task c0;
            // assign the attributes of completed task to the other task object to handle output
            c0.id = t->id;
            c0.value = t->value;
            c0.unit_count = t->unit_count;
            c0.execution_time = t->execution_time;
            ct[c0.id] = c0;
            num_tasks++;
            pthread_mutex_unlock(&realloc_mutex);
            pthread_mutex_lock(&completed_mutex);
            // increment completed_tasks by one
            completed_tasks++;
            pthread_mutex_unlock(&completed_mutex);
            usleep(500000); // make the thread sleep for 500,000 microseconds = 0.5 seconds
        }
    }
    /*
        If one unit notifies that the program has executed all the tasks, it will wake
        the dispatcher and by its turn, it will wake the uninformed units

        sometimes more than one units got notified, so by using dispatcher_status
        we can avoid losting dispatcher_waker
    */
    if (!dispatcher_status)
    {
        dispatcher_waker();
    }
    // print indicating message that the unit has finished its job
    printf("unit[%d] has no tasks, now it is exiting !\n", u->unit_id);
    // exit the thread
    pthread_exit(NULL);
}
// declare and initialize a function that handle the power operation
long long power(long long base, int power)
{
    // a container
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
    // loop until all the tasks have been read by the receptor and completed by the units
    while (!(receptor_done == true && total_tasks == completed_tasks))
    {
        Task *t = dequeue_unit(u); // fetching the task from the queue
        // check whether the t is NULL which indicate the end of all tasks
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
            // make th thread sleep for 50,000 microseconds = 0.5 seconds
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
            pthread_mutex_lock(&realloc_mutex);
            if (capacity < t->id)
            {
                while (capacity < t->id)
                {
                    capacity *= 2;
                }
                Completed_task *tmp = realloc(ct, capacity * sizeof(Completed_task));
                if (!tmp)
                {
                    pthread_mutex_unlock(&realloc_mutex);
                    perror("realloc failed\n");
                    exit(1);
                }
                ct = tmp;
            }
            Completed_task c0;
            // assign the attributes of completed task to the other task object to handle output
            c0.id = t->id;
            c0.value = t->value;
            c0.unit_count = t->unit_count;
            c0.execution_time = t->execution_time;
            ct[c0.id] = c0;
            num_tasks++;
            pthread_mutex_unlock(&realloc_mutex);
            pthread_mutex_lock(&completed_mutex);
            // increment completed_tasks by one
            completed_tasks++;
            pthread_mutex_unlock(&completed_mutex);
            usleep(500000); // make the thread sleep for 500,000 microseconds = 0.5 seconds
        }
    }
    /*
        If one unit notifies that the program has executed all the tasks, it will wake
        the dispatcher and by its turn, it will wake the uninformed units

        sometimes more than one units got notified, so by using dispatcher_status
        we can avoid losting dispatcher_waker
    */
    if (!dispatcher_status)
    {
        dispatcher_waker();
    }
    // print indicating message that the unit has finished its job
    printf("unit[%d] has no tasks, now it is exiting !\n", u->unit_id);
    // exit the thread
    pthread_exit(NULL);
}
void *unit_3(void *uq)
{
    UnitQueue *u = (UnitQueue *)uq;
    // loop until all the tasks have been read by the receptor and completed by the units
    while (!(receptor_done == true && total_tasks == completed_tasks))
    {
        Task *t = dequeue_unit(u); // fetching the task from the queue
        // check whether the t is NULL which indicate the end of all tasks
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
            // make th thread sleep for 50,000 microseconds = 0.5 seconds
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
            pthread_mutex_lock(&realloc_mutex);
            if (capacity < t->id)
            {
                while (capacity < t->id)
                {
                    capacity *= 2;
                }
                Completed_task *tmp = realloc(ct, capacity * sizeof(Completed_task));
                if (!tmp)
                {
                    pthread_mutex_unlock(&realloc_mutex);
                    perror("realloc failed\n");
                    exit(1);
                }
                ct = tmp;
            }
            Completed_task c0;
            // assign the attributes of completed task to the other task object to handle output
            c0.id = t->id;
            c0.value = t->value;
            c0.unit_count = t->unit_count;
            c0.execution_time = t->execution_time;
            ct[c0.id] = c0;
            num_tasks++;
            pthread_mutex_unlock(&realloc_mutex);
            pthread_mutex_lock(&completed_mutex);
            // increment completed_tasks by one
            completed_tasks++;
            pthread_mutex_unlock(&completed_mutex);
            usleep(500000); // make the thread sleep for 500,000 microseconds = 0.5 seconds
        }
    }
    /*
        If one unit notifies that the program has executed all the tasks, it will wake
        the dispatcher and by its turn, it will wake the uninformed units

        sometimes more than one units got notified, so by using dispatcher_status
        we can avoid losting dispatcher_waker
    */
    if (!dispatcher_status)
    {
        dispatcher_waker();
    }
    // print indicating message that the unit has finished its job
    printf("unit[%d] has no tasks, now it is exiting !\n", u->unit_id);
    // exit the thread
    pthread_exit(NULL);
}
void *unit_4(void *uq)
{
    UnitQueue *u = (UnitQueue *)uq;
    // loop until all the tasks have been read by the receptor and completed by the units
    while (!(receptor_done == true && total_tasks == completed_tasks))
    {
        Task *t = dequeue_unit(u); // fetching the task from the queue
        // check whether the t is NULL which indicate the end of all tasks
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
            // make th thread sleep for 50,000 microseconds = 0.5 seconds
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
            pthread_mutex_lock(&realloc_mutex);
            if (capacity < t->id)
            {
                while (capacity < t->id)
                {
                    capacity *= 2;
                }
                Completed_task *tmp = realloc(ct, capacity * sizeof(Completed_task));
                if (!tmp)
                {
                    pthread_mutex_unlock(&realloc_mutex);
                    perror("realloc failed\n");
                    exit(1);
                }
                ct = tmp;
            }
            Completed_task c0;
            // assign the attributes of completed task to the other task object to handle output
            c0.id = t->id;
            c0.value = t->value;
            c0.unit_count = t->unit_count;
            c0.execution_time = t->execution_time;
            ct[c0.id] = c0;
            num_tasks++;
            pthread_mutex_unlock(&realloc_mutex);
            pthread_mutex_lock(&completed_mutex);
            // increment completed_tasks by one
            completed_tasks++;
            pthread_mutex_unlock(&completed_mutex);
            usleep(500000); // make the thread sleep for 500,000 microseconds = 0.5 seconds
        }
    }
    /*
        If one unit notifies that the program has executed all the tasks, it will wake
        the dispatcher and by its turn, it will wake the uninformed units

        sometimes more than one units got notified, so by using dispatcher_status
        we can avoid losting dispatcher_waker
    */
    if (!dispatcher_status)
    {
        dispatcher_waker();
    }
    // print indicating message that the unit has finished its job
    printf("unit[%d] has no tasks, now it is exiting !\n", u->unit_id);
    // exit the thread
    pthread_exit(NULL);
}