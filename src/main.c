/*
    Source name: main.c
    Version: 2.0
    Created date: 21/12/2025
    Modified date: 31/12/2025
    Author: UNIX Team
    Description: This system simulates a high-performance multi-unit processing environment.
    Tasks are parsed from a file, entered into a global queue, and then navigated
    through a series of specialized worker threads (Units 0-4) based on a custom itinerary.

    Compile and Link: gcc main.c receptor.c dispatcher.c waiting_queue.c
    unit_queue.c units.c -o main -lpthread -lrt

    Run: ./main task.txt
*/
#include "../include/project.h"

// allocatememory for the waiting queue
WaitingQueue *wQueue;
// allocate memory for the unit queues
UnitQueue *uQueue[UNITS_NUMBER];
// declare and intialize an integer to identify the receptor status
bool receptor_done = false;
// declare and intialize an integer to count the total tasks
int total_tasks = 0;
// declare and intialize an integer to count the completed tasks
int completed_tasks = 0;
// declare and intialize a default values to dispatcher and units status
bool dispatcher_status = false;
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
        // assign to each unit_id its appropriate value
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
        printf("the receptor thread has not been created.\n");
        exit(1);
    }
    // check whether the dispatcher thread has been created
    if (pthread_create(&dispatcher_id, NULL, dispatcher, (void *)wQueue) < 0)
    {
        printf("the dispatcher thread has not been created.\n");
        exit(1);
    }
    // check whether the unit threads have been created
    if (pthread_create(&unit_ids[0], NULL, unit_0, (void *)uQueue[0]) < 0)
    {
        printf("the unit [0] thread has not been created.\n");
        exit(1);
    }
    if (pthread_create(&unit_ids[1], NULL, unit_1, (void *)uQueue[1]) < 0)
    {
        printf("the unit [1] thread has not been created.\n");
        exit(1);
    }
    if (pthread_create(&unit_ids[2], NULL, unit_2, (void *)uQueue[2]) < 0)
    {
        printf("the unit [2] thread has not been created.\n");
        exit(1);
    }
    if (pthread_create(&unit_ids[3], NULL, unit_3, (void *)uQueue[3]) < 0)
    {
        printf("the unit [3] thread has not been created.\n");
        exit(1);
    }
    if (pthread_create(&unit_ids[4], NULL, unit_4, (void *)uQueue[4]) < 0)
    {
        printf("the unit [4] thread has not been created.\n");
        exit(1);
    }
    // make the main thread waiting for the threads
    pthread_join(receptor_id, NULL);
    // wait for the dispatcher to finish
    pthread_join(dispatcher_id, NULL);
    // wait until all threads finishing its execution
    for (int i = 0; i < UNITS_NUMBER; i++)
    {
        pthread_join(unit_ids[i], NULL);
    }
    // print indicating message that all units threads have been exited
    printf("all the unit threads exited.\n");
    // print a message to indicate the end of the program
    printf("the prgoram has finished %d tasks successfully !\n", total_tasks);
    printf("تم بحمد الله وعونه\n { قُلْ إِنَّ صَلَاتِي وَنُسُكِي وَمَحْيَايَ وَمَمَاتِي لِلَّهِ رَبِّ الْعَالَمِينَ (162) لَا شَرِيكَ لَهُ وَبِذَٰلِكَ أُمِرْتُ وَأَنَا أَوَّلُ الْمُسْلِمِينَ (163) سورة الأنعام } \n");
    // free the waiting queue
    free(wQueue);
    // free the unit queues
    for (int i = 0; i < UNITS_NUMBER; i++)
    {
        free(uQueue[i]);
    }
    return 0;
}