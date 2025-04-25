#include <iostream>
#include <assert.h>
namespace MySTL{

template<typename T>
class Node{
public:
    Node* next = nullptr;
    T data;
};

template<typename T>
class stack{
    Node<T>* head = nullptr;
    int length = 0;
public:
    T top();
    void push(T val);
    void pop();
    size_t size();
    bool empty();
};

template<typename T>
T stack<T>::top(){
    assert(head != nullptr);
    return head->data;
}

template<typename T>
void stack<T>::push(T val){
    Node<T>* new_node = new Node<T>;
    new_node->data = val;
    new_node->next = head;
    head = new_node;
    length++;
}

template<typename T>
void stack<T>::pop(){
    assert(head != nullptr);
    Node<T>* temp = head;
    head = head->next;
    delete temp;
    length--;
}

template<typename T>
size_t stack<T>::size(){
    return length;
} 

template<typename T>
bool stack<T>::empty(){
    return head == nullptr;
}

}

int main(int argc, char ** argv){
    MySTL::stack<int> myStack;
    for(int i = 0; i < 10; i++)
        myStack.push(i);
    assert(myStack.top() == 9); 
    assert(myStack.size() == 10);
    while(!myStack.empty()){
        std::cout << myStack.top() << std::endl;
        myStack.pop();
    }
    
    return 0;
}