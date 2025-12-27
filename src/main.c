#include "../include/project.h"

main(int argc, char *argv[])
{
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
    if (pthread_create(&receptor_id, NULL, receptor, wQueue) < 0)
    {
        printf("the receptor thread has not been created successfully.\n");
        exit(1);
    }
    // check whether the dispatcher thread has been created
    if (pthread_create(&dispatcher_id, NULL, dispatcher, wQueue) < 0)
    {
        printf("the dispatcher thread has not been created successfully.\n");
        exit(1);
    }
    // check whether the unit threads have been created
    if (pthread_create(&unit_ids[0], NULL, unit_0, uQueue[0]) < 0)
    {
        printf("the unit [0] thread has not been created successfully.\n");
        exit(1);
    }
    if (pthread_create(&unit_ids[1], NULL, unit_1, uQueue[1]) < 0)
    {
        printf("the unit [1] thread has not been created successfully.\n");
        exit(1);
    }
    if (pthread_create(&unit_ids[2], NULL, unit_2, uQueue[2]) < 0)
    {
        printf("the unit [2] thread has not been created successfully.\n");
        exit(1);
    }
    if (pthread_create(&unit_ids[3], NULL, unit_3, uQueue[3]) < 0)
    {
        printf("the unit [3] thread has not been created successfully.\n");
        exit(1);
    }
    if (pthread_create(&unit_ids[4], NULL, unit_4, uQueue[4]) < 0)
    {
        printf("the unit [4] thread has not been created successfully.\n");
        exit(1);
    }
    // make the main thread waiting for the threads
    pthread_join(&receptor_id, NULL);
    pthread_join(&dispatcher_id, NULL);
    for (int i = 0; i < UNITS_NUMBER; i++)
    {
        pthread_join(unit_ids[i], NULL);
    }
    // print a message to indicate the end of the program
    printf("the prgoram finished %d tasks successfully !\n", total_tasks);
}