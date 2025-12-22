#include "../include/project.h"
#include "queue.c"

int main() {
    Queue test_q;
    queue_init(&test_q);

    // Create a dummy task to test with
    Task *t1 = malloc(sizeof(Task));
    t1->id = 101;
    t1->value = 500;
    Task *t2 = malloc(sizeof(Task));
    t2->id = 102;
    t2->value = 500;
    Task *t3 = malloc(sizeof(Task));
    t3->id = 103;
    t3->value = 500;

    printf("Testing Enqueue...\n");
    enqueue(&test_q, t1);
    enqueue(&test_q, t2);
    enqueue(&test_q, t3);

    printf("Testing Dequeue...\n");
    Task *received = dequeue(&test_q);

    if (received->id == 101) {
        printf("✅ Success! Task ID matches.\n");
    } else {
        printf("❌ Fail! Expected ID 101, got %d\n", received->id);
    };
    Task *received2 = dequeue(&test_q);

    if (received2->id == 102) {
        printf("✅ Success! Task ID matches.\n");
    } else {
        printf("❌ Fail! Expected ID 101, got %d\n", received->id);
    };
    Task *received3 = dequeue(&test_q);

    if (received3->id == 103) {
        printf("✅ Success! Task ID matches.\n");
    } else {
        printf("❌ Fail! Expected ID 101, got %d\n", received->id);
    };

    return 0;
}