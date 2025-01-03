#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

Queue* init_queue(){
    Queue * q = (Queue *)malloc(sizeof(Queue));
    q->front = NULL;
    q->rear = NULL;
    return q;
}

void push(Queue* q , int value){
    Node* tmp = (Node *)malloc(sizeof(Node));
    tmp->data = value;
    tmp->next = NULL;

    if(q->rear == NULL){
        q->front = q->rear = tmp;
    }else{
        q->rear->next = tmp;
        q->rear = q->rear->next;
    }
}

int pop(Queue* q){
    if(q->front == NULL){
        fprintf(stderr, "queue is empty.\n");
        exit(0);
    }
    Node* tmp = q->front;
    q->front = q->front->next;
    if(q->front == NULL){
        q->rear = NULL;
    }
    int value = tmp->data;
    free(tmp);
    return value;
}

int is_empty(Queue* q){
    return q->front == NULL;
}

void free_queue(Queue* q){
    while(!is_empty(q)){
        pop(q);
    }
    free(q);
}