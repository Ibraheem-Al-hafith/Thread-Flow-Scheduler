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
    while (receptor_done == false || q->rear != 0 || q->front != 0)
    {
        // 1. Pull
        Task *t = dequeue(q);

        // 2. Identify
        int target_unit = t->unit_ids[t->current_step];

        // 3. Forward
        enqueue_unit(uQueue[target_unit], t);

        printf("Dispatcher: Task %d sent to Unit %d successfully!\n", t->id, target_unit);
    }
    // printf("Dispatcher: No more tasks to dispatch. Exiting...\n");
    // pthread_exit(NULL);
}