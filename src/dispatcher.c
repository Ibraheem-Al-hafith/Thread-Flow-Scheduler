/*
    Dispatcher:
    for the lifetime of the program, the dispatcher is responsible for :
    1. read from the waiting queue.
    2. get the task unit id.
    3. pass the task to the desired unit.

*/
#include "../include/project.h"

void *dispatcher(void *wq)
{
    struct timespec ts;
    ts.tv_sec = 1; // 1 second
    ts.tv_nsec = 0;
    // casting from void to waitingqueue
    WaitingQueue *q = (WaitingQueue *)wq;
    // let the dispatcher looping until the receptor is done and the completed tasks equal the total tasks
    while (!(receptor_done == true && total_tasks == completed_tasks))
    {
        // 1. Pull
        Task *t = dequeue(q);
        // when the return is NULL it means the receptor is done and all tasks have been processed
        if (t == NULL)
        {
            break;
        }
        // 2. Identify
        int target_unit = t->unit_ids[t->current_step];

        // 3. insert the task into the appropriate unit queue
        enqueue_unit(uQueue[target_unit], t);
        // print an indicating message of inserting the task
        printf("Dispatcher: Task %d sent to Unit %d successfully!\n", t->id, target_unit);
    }
    /*
        after the dispatcher finished its job, signal all the waiting unit queues
        to avoid waiting for nothing which causes the program to hanging
    */
    for (int i = 0; i < UNITS_NUMBER; i++)
    {
        // signal all the waiting unit queues
        pthread_cond_signal(&uQueue[i]->not_empty);
        // wait until all unit threads exit
        nanosleep(&ts, NULL);
    }
    // print a message indicating that the dispatcher has finished
    printf("dispatcher has finished\n");
    // change the status to true to notify the units
    dispatcher_status = true;
    // exit the thread
    pthread_exit(NULL);
}