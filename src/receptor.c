/*
    Receptor:
        It reads all the tasks from a file and insert them one by one
        into the waiting queue
*/
#include "../include/project.h"

void *receptor(void *arg)
{
    // get the file name
    char *filename = (char *)arg;
    // open the file for reading
    FILE *f = fopen(filename, "r");
    if (!f)
    {
        // print an error meassge to indicate a problem in opening the file
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    // reserve an array to hold the line
    char line[1024];
    while (fgets(line, sizeof(line), f))
    {
        // assign the splitted values to the task structure
        Task *t;
        // allocate memory for the task object
        t = (Task *)malloc(sizeof(Task));
        // skip blank lines and comments that start with '#'
        if (line[0] == '\n' || line[0] == '#')
            continue;
        // Expected line format: <id> <value> <units_count> <unit-id-1> ...

        // initialize an integer for the task id
        int id;
        // initialize an integer for the unit count
        int uc;
        // initialize an integer for the task value
        long long val;
        // split the values in the line according to spaces, tab, and newline
        char *tok = strtok(line, " \t\n");
        // if tok is NULL continue and get next line
        if (!tok)
            continue;
        // otherwise, assign the task id to id
        id = atoi(tok);
        // continue from last position, the same manner
        tok = strtok(NULL, " \t\n");
        if (!tok)
            continue;
        // assign it to val
        val = atoi(tok);
        tok = strtok(NULL, " \t\n");
        if (!tok)
            continue;
        // assign the value to uc
        uc = atoi(tok);
        // allocate array of requested unit ids in sequence
        // multiply the size of integer by uc
        int *uids = malloc(sizeof(int) * uc);
        for (int i = 0; i < uc; ++i)
        {
            tok = strtok(NULL, " \t\n");
            if (!tok)
            {
                // if a value does not found, make the default unit 0
                uids[i] = 0;
            }
            else
                // otherwise assign the value
                uids[i] = atoi(tok);
        }
        // assign the value we got to the attributes of the task object
        t->id = id;
        t->value = val;
        t->unit_count = uc;
        t->unit_ids = uids;
        t->current_step = 0;
        // assign a 0 value to the arrival time until it is added to the waiting queue
        t->atime.tv_sec = 0;
        t->atime.tv_nsec = 0;
        // update global counters and enqueue the task
        enqueue(wQueue, t);
        // print a message that indicate the inserting of the task
        printf("task[%d] inserted\n", t->id);
        // increment of total tasks by one
        total_tasks++;
    }
    // close the file
    fclose(f);
    // change the receptor_done to 1 to indicate the end of receptor function
    receptor_done = true;
    // print a message that indicate the finishing of the receptor
    printf("all the tasks have been read successfully by the receptor.\n");
    // exit the thread
    pthread_exit(NULL);
}
