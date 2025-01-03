#include "queue.h"

int main(int argc , char ** argv){
    Queue* q = init_queue();

    push(q, 10);
    push(q, 20);
    push(q, 30);

    printf("Dequeued: %d\n", pop(q));
    printf("Dequeued: %d\n", pop(q));
    printf("Dequeued: %d\n", pop(q));

    free_queue(q);
    return 0;
}