#include "../include/project.h"

void queue_init(Queue *q) {
    q->head = NULL;
    q->tail = NULL;

    // Inititalize the synchronization tools
    pthread_mutex_init(&q->lock, NULL);
    pthread_cond_init(&q->notify, NULL);
}

/*
Here is the logic for Enqueue:

    1. Create a new Node and set its task pointer.

    2. Lock the Mutex. 🔒

    3. Attach the node to the tail of the list.

    4. Signal the condition variable. 📣

    5. Unlock the Mutex. 🔓
*/


void enqueue(Queue *q, Task *t){
    // 1. create the new node
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->task = t;
    newNode->next = NULL;

    // 2. lock the door (mutex) so no one else touches the pointers while we adding the task
    pthread_mutex_lock(&q->lock);

    // 3. Attach the node to the list
    if (q->tail == NULL) {
        // the queue is empty, so the head and tail would be our node
        q->head = newNode;
        q->tail = newNode;
    } else {
        // add our node at the end of the list
        q->tail->next = newNode;
        q->tail = newNode;
    }

    // 4. wake up a waiting thread (if any)
    pthread_cond_signal(&q->notify);

    // 5. unlock the door
    pthread_mutex_unlock(&q->lock);
}


/*
Here is the logic for dequeue:
    1. Lock the mutex.

    2. Wait if the list is empty (q->head == NULL).

    3. Take the task from the head.

    4. Move the head pointer to the next node.

    5. Unlock and return the task.
    When the Dispatcher (or any unit) calls this,
    it tells the OS: "I'm going to sleep now.
    Please wake me up when someone signals this specific condition variable.""
    The cool part is that pthread_cond_wait automatically unlocks the mutex
    for you while you sleep so other threads can use the queue. When you wake up,
    it relocks the mutex automatically before letting the thread continue.
*/

Task* dequeue(Queue *q) {
    // 1. Get the key (lock the mutex)
    pthread_mutex_lock(&q->lock);

    // 2. Wait while the queue is empty
    while (q->head == NULL){
        pthread_cond_wait(&q->notify, &q->lock);
    }

    // 3. Take the task from the head.
    Node *temp = q->head;
    Task *t = temp->task;

    // 4. Move the head pointer to the next node.
    q->head = q->head->next;
    // If the queue is now empty, reset the tail too
    if (q->head == NULL) {
        q->tail = NULL;
    }

    // 5. Unlock and return the task.
    free(temp); // Free the node memory (NOT THE TASK!!)
    pthread_mutex_unlock(&q->lock);

    return t;
}
