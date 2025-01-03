#include "linked_list.h"

int main(int argc , char ** argv){
    LinkedList * list = init_linked_list();
    push(list , 10);
    push(list , 20);
    push(list , 30);
    push(list , 40);
    push(list , 50);
    print_linked_list(list);
    insert_at(list , 2 , 25);
    print_linked_list(list);
    delete_at(list , 2);
    print_linked_list(list);
    free_linked_list(list);
    return 0;
}