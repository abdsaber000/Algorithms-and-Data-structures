#ifndef QUEUE_H
#define QUEUE_H

typedef struct Node{
    int data;
    struct Node* next;
} Node;

typedef struct Queue{
    Node* front;
    Node* rear;
} Queue;


Queue* init_queue();
void push(Queue*,int);
int pop(Queue*);
int is_empty(Queue*);
void free_queue(Queue*);

#endif // QUEUE_H