#include "project.h"

void *receptor_thread(void *arg) {
    char *filename = (char *)arg;
    FILE *f = fopen(filename, "r");
    if (!f) { perror("fopen"); exit(EXIT_FAILURE); }
    char line[1024];
    while (fgets(line, sizeof(line), f)) {
        // skip blank lines and comments that start with '#'
        if (line[0] == '\n' || line[0] == '#') continue;
        // Expected line format: <id> <value> <units_count> <unit-id-1> ...
        char *s = line;
        int id, uc;
        long long val;
        char *tok = strtok(s, " \t\n");
        if (!tok) continue;
        id = atoi(tok);
        tok = strtok(NULL, " \t\n"); if (!tok) continue; val = atoll(tok);
        tok = strtok(NULL, " \t\n"); if (!tok) continue; uc = atoi(tok);
        // allocate array of requested unit ids in sequence
        int *uids = malloc(sizeof(int) * uc);
        for (int i = 0; i < uc; ++i) {
            tok = strtok(NULL, " \t\n");
            if (!tok) { uids[i] = 0; } else uids[i] = atoi(tok);
        }
        // create task structure and record arrival time
        task_t *t = malloc(sizeof(task_t));
        t->id = id; t->value = val; t->unit_count = uc; t->unit_ids = uids; t->current_idx = 0;
        clock_gettime(CLOCK_REALTIME, &t->arrival);
        // update global counters and enqueue the task
        pthread_mutex_lock(&count_lock); total_tasks++; pthread_mutex_unlock(&count_lock);
        queue_push(&waiting_q, t);
    }
    fclose(f);
    receptor_done = 1;
    // wake dispatcher if waiting
    pthread_cond_broadcast(&waiting_q.cond);
    return NULL;
}
