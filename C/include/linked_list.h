#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct LinkedList {
    Node* head;
    Node* tail;
    int size;
} LinkedList;

LinkedList * init_linked_list();
void push(LinkedList * list , int val);
Node* get_at(LinkedList *list , int index);
void insert_at(LinkedList *list , int index , int val);
void delete_at(LinkedList *list , int index);
void print_linked_list(LinkedList *list);
void free_linked_list(LinkedList *list);

#endif // LINKED_LIST_H
