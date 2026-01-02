/*
    Source name: main.c
    Version: 2.0
    Created date: 21/12/2025
    Modified date: 02/01/2026
    Author: UNIX Team
    1. Ibrahim Alhafith Alkhair Yousif | Statistics & Computer Science | 20-101
    2. Rashed Albasheir Suliman Fadl-Allah | Statistics & Computer Science | 20-204
    3. Mohammed Salah Ahmed Mohammed | Computer Science | 20-310
    4. Mosab Taha Ahmed Elmukashfi | Computer Science | 20-312
    5. Awaab Abdelrafia Ballah Mohammed | Computer Science | 20-306

    Description: This system simulates a high-performance multi-unit processing environment.
    Tasks are parsed from a file, entered into a global queue, and then navigated
    through a series of specialized worker threads (Units 0-4) based on a custom itinerary.

    Compile and Link: gcc main.c receptor.c dispatcher.c waiting_queue.c
    unit_queue.c units.c -o main -lpthread -lrt

    Run: ./main task.txt
    * If you have list of tasks you can use your file by replacing task.txt with your file name
*/
#include "../include/project.h"

// allocate memory for the waiting queue
WaitingQueue *wQueue;
// allocate memory for the unit queues
UnitQueue *uQueue[UNITS_NUMBER];
// declare and intialize a bool variable to identify the receptor status
bool receptor_done = false;
// declare and intialize an integer to count the total tasks
int total_tasks = 0;
// declare and intialize an integer to count the completed tasks
int completed_tasks = 0;
// declare an integer for the capacity of the completed tasks array (initial capacity is 128)
int capacity = QUEUE_CAPACITY;
// declare and intialize a default values to dispatcher and units status
Completed_task *ct;
// declare an integer to count the number of tasks inserted into the task array used for the output
int num_tasks = 0;
// declare and intialize a bool variable to save the status of the dispatcher (default is false)
bool dispatcher_status = false;
int main(int argc, char *argv[])
{
    // create an output file to store the completed tasks
    FILE *fp = fopen("completed_tasks.txt", "w");
    // allocate a memory size of 128 as inital size and then expand if needed
    ct = (Completed_task *)calloc(QUEUE_CAPACITY, sizeof(Completed_task));
    // get the input file name
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
    // print the introduction message
    printf("بسم الله الرحمن الرحيم\n");
    printf("<-------------------------------------------------------------------------->\n");
    printf("\t\tUNIX Team Thread Flow Scheduler Project\n");
    printf("<-------------------------------------------------------------------------->\n");
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
    for (int i = 0; i < UNITS_NUMBER; i++)
    {
        if (pthread_create(&unit_ids[i], NULL, units, (void *)uQueue[i]) < 0)
        {
            printf("the unit [%d] thread has not been created.\n", i);
            exit(1);
        }
    }
    // make the main thread waiting for the threads
    pthread_join(receptor_id, NULL);
    // sleep for 0.01 seconds before creating the dispatcher to give some time until receptor insert some tasks
    // create a timer for the nanosleep
    struct timespec dt;
    dt.tv_sec = 0;          // 0 seconds
    dt.tv_nsec = 100000000; // 10,000,000 nanoseconds  = 0.01 second
    // send it to sleep
    nanosleep(&dt, NULL);
    // wait for the dispatcher to finish
    pthread_join(dispatcher_id, NULL);
    // wait until all threads finishing its execution
    for (int i = 0; i < UNITS_NUMBER; i++)
    {
        pthread_join(unit_ids[i], NULL);
    }
    // print indicating message that all units threads have been exited
    printf("all the unit threads exited.\n");
    // write into the output file all the completed tasks from the output array ct
    for (int i = 0; i < num_tasks; i++)
    {
        fprintf(fp, "task[%d] visit %d unit(s): result = {%lld}, elapsed time is {%.9f} seconds\n", ct[i].id, ct[i].unit_count, ct[i].value, ct[i].execution_time);
    }
    // close the file
    fclose(fp);
    // free the output array
    free(ct);
    // print a message to indicate the end of the program
    printf("the prgoram has finished %d tasks successfully and store them in an output file: %s !\n", total_tasks, "completed_tasks.txt");

    // print the most important message that thanking Allah for all his grace and mercy
    printf("تم بحمد الله وعونه\n\nقُلْ إِنَّ صَلَاتِي وَنُسُكِي وَمَحْيَايَ وَمَمَاتِي لِلَّهِ رَبِّ الْعَالَمِينَ (162) لَا شَرِيكَ لَهُ وَبِذَٰلِكَ أُمِرْتُ وَأَنَا أَوَّلُ الْمُسْلِمِينَ (163)\nسورة الأنعام\n");
    // free the waiting queue
    free(wQueue);
    // free the unit queues
    for (int i = 0; i < UNITS_NUMBER; i++)
    {
        free(uQueue[i]);
    }
    return 0;
}