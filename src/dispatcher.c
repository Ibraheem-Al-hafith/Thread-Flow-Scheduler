#include "../include/project.h"

/*
Steps:
for the lifetime of the program, the dispatcher is responsible for :
    1. read from the waiting queue.
    2. get the task unit id.
    3. pass the task to the desired unit.

*/
void *dispatcher(void *wq)
{
    WaitingQueue *q = (WaitingQueue *)wq;
    while (1)
    {
        // 1. Pull
        Task *t = dequeue(q);
        if (t == NULL)
        {
            break;
        }
        // 2. Identify
        int target_unit = t->unit_ids[t->current_step];

        // 3. Forward
        enqueue_unit(uQueue[target_unit], t);

        printf("Dispatcher: Task %d sent to Unit %d successfully!\n", t->id, target_unit);
    }
    for (int i = 0; i < UNITS_NUMBER; i++)
    {
        pthread_cond_signal(&uQueue[i]->not_empty);
        // wait until all unit threads exit
        usleep(100000);
    }
    printf("dispatcher has finished\n");
    dispatcher_status = true;
    pthread_exit(NULL);
}