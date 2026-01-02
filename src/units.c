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
pthread_mutex_t s_mutex;

// declare and initialize a function that handle the power operation
long long power(long long base, int power)
{
    // a container
    long long result = 1;
    // perform the power operation
    for (int i = 0; i < power; i++)
    {
        result *= base;
    }
    return result;
}
void *units(void *uq)
{
    // define an object to use as a timer for the sleep of unit after each execution by 0.5 second
    struct timespec ts;
    ts.tv_sec = 0;          // 0 seconds
    ts.tv_nsec = 500000000; // 500,000,000 nanoseconds = 0.5 seconds
    // casting from void to unitQueue type
    UnitQueue *u = (UnitQueue *)uq;
    // let the unit looping until the receptor is done and the completed tasks equal the total tasks
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
        /*
            This function (void *units) is used by all the threads and all of them executes all the previous
            lines so we do not need to give each thread its own function and dupliate the same code, but after them
            we should let each unit thread executes seperately and this can be done
            by using switch structure along with the unit's ID
        */
        switch (u->unit_id)
        {
        // unit 0
        case 0:
            temp = (temp + 7) % M; // execute the unit operation
            t->value = temp;       // update the task value
            break;
        // unit 1
        case 1:
            temp = (temp * 2) % M; // execute the unit operation
            t->value = temp;       // update the task value
            break;
        // unit 2
        case 2:
            temp = power(temp, 5); // execute the unit operation
            temp = temp % M;       // after we getting the power of 5, we calculate the mod operation
            t->value = temp;       // update the task value
            break;
        // unit 3
        case 3:
            temp = (temp - 19); // execute the unit operation
            t->value = temp;    // update the task value
            break;
        // unit 4
        case 4:
            // display a message to indicate the status of a task after being proccessed
            printf("the value of the task[%d] after being processed is {%lld}\n", t->id, t->value);
            break;
        }
        /*
            all the next line are executed by all the unit threads again
        */
        t->current_step++; // increment the current step by one
        //  check if the task is completed or not
        // if it is not completed, insert again into the waiting queue
        struct timespec ut;
        ut.tv_sec = 0;
        ut.tv_nsec = 100000000;
        if (t->current_step < t->unit_count)
        {
            // let the unit wait to avoid problems of full of waiting queue
            nanosleep(&ut, NULL);
            enqueue(wQueue, t); // insert the task again into the waiting queue
            // make the thread sleep for 0.5 seconds
            nanosleep(&ts, NULL);
        }
        // otherwise get its execution time and print an indicating message, also handle the inserting of the task into the output array
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
            // lock the mutex to ensure safety and avoid conflict and corruption of reallocate by two threads in same time !
            pthread_mutex_lock(&realloc_mutex);
            /*
                The next code is used to expand the size of the output array when it is needed
                we initialize the size by 128 elements toreserve a space in memory and then expand it.
                If someone asks why you did not initialize the actual size, this is because the actual number of tasks appear
                during the run time and we can make the receptor finishing its job but this will make the others waiting for it
                for long time if the number of tasks is big
            */
            if (capacity < t->id)
            {
                // loop until the capacity is greater than the entered task ID
                while (capacity < t->id)
                {
                    // multiply it by 2
                    capacity *= 2;
                }
                /* after getting the new capacity, reallocate the memory and saving the other data in previous array
                  this can be done by realloc function. We used tmp object to avoid problems such as failing of reallocating
                  memory which leads to losing of the output array data
                */
                Completed_task *tmp = realloc(ct, capacity * sizeof(Completed_task));
                // if it fails, print a message of failing
                if (!tmp)
                {
                    pthread_mutex_unlock(&realloc_mutex);
                    perror("realloc failed\n");
                    exit(1);
                }
                // otherwise, let ct points to the new expanded memory location
                ct = tmp;
            }
            // after each execution of unit thread, create an object that holds the dataneeded for the output file
            Completed_task c_t;
            // assign the attributes of completed task to the other task object to handle output
            c_t.id = t->id;
            c_t.value = t->value;
            c_t.unit_count = t->unit_count;
            c_t.execution_time = t->execution_time;
            ct[c_t.id] = c_t;
            // increment the number of tasks by one, it will be used as a counter in main file to write into the output file
            num_tasks++;
            // unlock the mutex to enable other threads to insert task and realloc if needed
            pthread_mutex_unlock(&realloc_mutex);
            // lock the mutex to ensure saftey for the next global variable
            pthread_mutex_lock(&completed_mutex);
            // increment completed_tasks by one
            completed_tasks++;
            // unlock the mutex
            pthread_mutex_unlock(&completed_mutex);
            nanosleep(&ts, NULL); // make the thread sleep for 500,000 microseconds = 0.5 seconds
        }
    }
    /*
        If one unit notified that the program has executed all the tasks, it will wake
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