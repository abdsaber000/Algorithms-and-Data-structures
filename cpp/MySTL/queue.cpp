#include <iostream>
#include <assert.h>

namespace MySTL{
template<typename T>
class Node{
public:
    T data;
    Node* next = nullptr;
};

template<typename T>
class queue{
    Node<T>* head = nullptr;
    Node<T>* tail = nullptr;
    size_t length = 0;
public:
    void push(T val);
    void pop();
    T front();
    size_t size();
    bool empty();
    ~queue();
};

template<typename T>
auto queue<T>::push(T val) -> void{
    Node<T>* new_node = new Node<T>;
    new_node->data = val;
    if(tail){
        tail->next = new_node;
        tail = tail->next;
    }else{
        tail = new_node;
    }

    if(!head){
        head = new_node;
    }
    length++;
}

template<typename T>
auto queue<T>::pop() -> void {
    assert(head != nullptr);
    auto tmp = head->next;
    delete head;
    head = tmp;
    length--;
}


template<typename T>
auto queue<T>::front() -> T {
    assert(head != nullptr);
    return head->data;
}

template<typename T>
auto queue<T>::size() -> size_t {
    return length;
}

template<typename T>
queue<T>::~queue() {
    while(head != nullptr){
        auto tmp = head->next;
        delete head;
        head = tmp;
    }
    tail = nullptr;
    length = 0;   
}

}

int main(int argc, char** argv){
    MySTL::queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);
    assert(q.front() == 1);
    assert(q.size() == 3);
    q.pop();
    assert(q.front() == 2);
    assert(q.size() == 2);
    q.pop();
    assert(q.front() == 3);
    assert(q.size() == 1);
    q.pop();
    assert(q.size() == 0);
    return 0;
}