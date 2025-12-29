#include "../include/project.h"
// allocatememory for the waiting queue
WaitingQueue *wQueue;
// allocate memory for the unit queues
UnitQueue *uQueue[UNITS_NUMBER];
// initialize and assign an integer to identify the receptor status
bool receptor_done = false;
// initialize and assign an integer to count the total tasks
int total_tasks = 0;
// initialize and assign an integer to count the completed tasks
int completed_tasks = 0;
// initialize and assign a default values to dispatcher and units status
bool dispatcher_status = false;
bool units_status[UNITS_NUMBER] = {false, false, false, false, false};
int main(int argc, char *argv[])
{
    // get the file name
    char *fname = argv[1];
    // allocate memory for waiting queue
    wQueue = (WaitingQueue *)malloc(sizeof(WaitingQueue));
    // allocate memory for unit queues
    for (int i = 0; i < UNITS_NUMBER; i++)
    {
        uQueue[i] = (UnitQueue *)malloc(sizeof(UnitQueue));
        uQueue[i]->unit_id = i;
    }
    // initalize the waiting queue
    queue_init(wQueue);
    // initalize the unit queues
    for (int i = 0; i < UNITS_NUMBER; i++)
    {
        unit_queue_init(uQueue[i]);
    }
    pthread_t receptor_id;   // create a thread for the receptor
    pthread_t dispatcher_id; // create a thread for the dispatcher
    pthread_t unit_ids[5];   // create threads for the unit
    // check whether the receptor thread has been created
    if (pthread_create(&receptor_id, NULL, receptor, (void *)fname) < 0)
    {
        printf("the receptor thread has not been created successfully.\n");
        exit(1);
    }
    // check whether the dispatcher thread has been created
    if (pthread_create(&dispatcher_id, NULL, dispatcher, (void *)wQueue) < 0)
    {
        printf("the dispatcher thread has not been created successfully.\n");
        exit(1);
    }
    // check whether the unit threads have been created
    if (pthread_create(&unit_ids[0], NULL, unit_0, (void *)uQueue[0]) < 0)
    {
        printf("the unit [0] thread has not been created successfully.\n");
        exit(1);
    }
    if (pthread_create(&unit_ids[1], NULL, unit_1, (void *)uQueue[1]) < 0)
    {
        printf("the unit [1] thread has not been created successfully.\n");
        exit(1);
    }
    if (pthread_create(&unit_ids[2], NULL, unit_2, (void *)uQueue[2]) < 0)
    {
        printf("the unit [2] thread has not been created successfully.\n");
        exit(1);
    }
    if (pthread_create(&unit_ids[3], NULL, unit_3, (void *)uQueue[3]) < 0)
    {
        printf("the unit [3] thread has not been created successfully.\n");
        exit(1);
    }
    if (pthread_create(&unit_ids[4], NULL, unit_4, (void *)uQueue[4]) < 0)
    {
        printf("the unit [4] thread has not been created successfully.\n");
        exit(1);
    }
    // make the main thread waiting for the threads
    pthread_join(receptor_id, NULL);
    pthread_join(dispatcher_id, NULL);
    int counter = 0;
    while (1)
    {
        if (counter == UNITS_NUMBER)
            break;
        else
        {
            if (!units_status[0])
            {
                pthread_cond_signal(&uQueue[0]->not_empty);
                counter++;
            }
            else if (!units_status[1])
            {
                pthread_cond_signal(&uQueue[1]->not_empty);
                counter++;
            }
            else if (!units_status[2])
            {
                pthread_cond_signal(&uQueue[2]->not_empty);
                counter++;
            }
            else if (!units_status[3])
            {
                pthread_cond_signal(&uQueue[3]->not_empty);
                counter++;
            }
            else if (!units_status[4])
            {
                pthread_cond_signal(&uQueue[4]->not_empty);
                counter++;
            }
        }
    }
    // print a message to indicate the end of the program
    printf("the prgoram finished %d tasks successfully !\n", total_tasks);
    return 0;
}