#include "linked_list.h"

LinkedList * init_linked_list(){
    LinkedList * list = (LinkedList *)malloc(sizeof(LinkedList));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

void push(LinkedList * list , int val){
    Node * new_node = (Node *)malloc(sizeof(Node));
    new_node->data = val;
    new_node->next = NULL;
    if(list->tail != NULL){
        list->tail->next = new_node;
    }
    list->tail = new_node;
    if(list->head == NULL){
        list->head = new_node;
    }
    list->size++;
}

Node* get_at(LinkedList *list , int index){
    if(index >= list->size || index < 0){
        return NULL;
    }
    Node * current = list->head;
    for(int i = 0; i < index; i++){
        current = current->next;
    }
    return current;
}

void insert_at(LinkedList *list , int index , int val){
    if(index > list->size || index < 0){
        return;
    }
    if(index == list->size){
        push(list , val);
        return;
    }
    Node * new_node = (Node *)malloc(sizeof(Node));
    new_node->data = val;
    if(index == 0){
        new_node->next = list->head;
        list->head = new_node;
    }else{
        Node * prev = get_at(list , index - 1);
        new_node->next = prev->next;
        prev->next = new_node;
    }
    list->size++;
}

void delete_at(LinkedList *list , int index){
    if(index >= list->size || index < 0){
        return;
    }
    Node * to_delete;
    if(index == 0){
        to_delete = list->head;
        list->head = list->head->next;
    }else{
        Node * prev = get_at(list , index - 1);
        to_delete = prev->next;
        prev->next = to_delete->next;
    }
    free(to_delete);
    list->size--;
}

void print_linked_list(LinkedList *list){
    Node * current = list->head;
    while(current != NULL){
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void free_linked_list(LinkedList *list){
    while(list->head != NULL){
        Node * to_delete = list->head;
        list->head = list->head->next;
        free(to_delete);
    }
    free(list);
}