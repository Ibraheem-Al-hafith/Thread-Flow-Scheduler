#include "../include/project.h"

main(int argc, char *argv[])
{
    // initalize the waiting queue
    queue_init(wQueue);
    // initalize the unit queues
    for (int i = 0; i < UNITS_NUMBER; i++)
    {
        unit_queue_init(u[i]);
    }
    pthread_t receptor_id; // create a thread for the receptor
    // check whether the receptor thread has been created
    if (pthread_create(&receptor_id, NULL, receptor, wQueue) < 0)
    {
        printf("the receptor thread has not been created successfully.\n");
        exit(1);
    }
    pthread_t dispatcher_id; // create a thread for the dispatcher
    if (pthread_create(&dispatcher_id, NULL, dispatcher, wQueue) < 0)
    {
        printf("the dispatcher thread has not been created successfully.\n");
        exit(1);
    }
    // make the main thread waiting for the threads
    pthread_join(&receptor_id, NULL);
    pthread_join(&dispatcher_id, NULL);
}