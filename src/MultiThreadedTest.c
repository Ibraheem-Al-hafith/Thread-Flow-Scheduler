#include "../include/project.h"
#include "../src/queue.c"
#include <unistd.h> // for sleep()

void* slow_producer(void* arg) {
    Queue *q = (Queue*)arg;
    printf("[Producer] Sleeping for 2 seconds...\n");
    sleep(2); 
    
    Task *t = malloc(sizeof(Task));
    t->id = 777;
    
    printf("[Producer] Adding task %d to queue!\n", t->id);
    enqueue(q, t);
    return NULL;
}

int main() {
    Queue q;
    queue_init(&q);
    pthread_t thread_id;

    // Start the producer thread
    pthread_create(&thread_id, NULL, slow_producer, &q);

    printf("[Main] Attempting to dequeue (should wait...)\n");
    Task *received = dequeue(&q); 
    
    printf("[Main] Success! Received Task ID: %d\n", received->id);
    
    pthread_join(thread_id, NULL);
    return 0;
}