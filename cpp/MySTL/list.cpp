#include <iostream>
#include <algorithm>
namespace MySTL{

template<typename T>
class Node{
public:
    T data;
    Node* next = nullptr;
    Node* prev = nullptr;
};

template<typename T>
class IteratorList : public std::iterator<std::bidirectional_iterator_tag, T> {
    Node<T>* ptr;
    public:

    IteratorList(Node<T>* p) : ptr(p) {}
    T& operator*() { return ptr->data; }
    IteratorList& operator++() { ptr = ptr->next; return *this; } // Prefix 
    IteratorList operator++(int) { // Postfix
        IteratorList temp = *this;
        ptr = ptr->next;
        return temp;
    }
    IteratorList& operator--() { ptr = ptr->prev; return *this; } // Prefix
    IteratorList operator--(int) { // Postfix
        IteratorList temp = *this;
        ptr = ptr->prev;
        return temp;
    }
    bool operator!=(const IteratorList& other) const { return ptr != other.ptr; }
    bool operator==(const IteratorList& other) const { return ptr == other.ptr; }
    ~IteratorList() { ptr = nullptr; } // Destructor to avoid dangling pointer
};

template<typename T>
class list{

    Node<T>* head = nullptr;
    Node<T>* tail = nullptr;
    size_t length = 0;
public:
    void push_back(T val);
    void pop_back();
    void push_front(T val);
    void pop_front();
    T& front();
    T& back();
    size_t size();
    IteratorList<T> begin() { return IteratorList<T>(head); }
    IteratorList<T> end() { return IteratorList<T>(nullptr); }
    ~list();
};

template<typename T>
void list<T>::push_back(T val){
    Node<T>* new_node = new Node<T>;
    new_node->data = val;
    if(tail){
        new_node->prev = tail;
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
void list<T>::push_front(T val){
    Node<T>* new_node = new Node<T>;
    new_node->data = val;
    if(head){
        new_node->next = head;
        head->prev = new_node;
        head = head->prev;
    }else{  
        head = new_node;
    }
    if(!tail){
        tail = new_node;
    }
    length++;
}

template<typename T>
void list<T>::pop_back(){
    if(tail){
        Node<T>* temp = tail;
        tail = tail->prev;
        if(tail){
            tail->next = nullptr;
        }else{
            head = nullptr;
        }
        delete temp;
        length--;
    }
}

template<typename T>
void list<T>::pop_front(){
    if(head){
        Node<T>* temp = head;
        head = head->next;
        if(head){
            head->prev = nullptr;
        }else{
            tail = nullptr;
        }
        delete temp;
        length--;
    }
}

template<typename T>
T& list<T>::front(){
    if(head){
        return head->data;
    }
    throw std::out_of_range("List is empty");
}

template<typename T>
T& list<T>::back(){
    if(tail){
        return tail->data;
    }
    throw std::out_of_range("List is empty");
}

template<typename T>
size_t list<T>::size(){
    return length;
}

template<typename T>
list<T>::~list(){
    Node<T>* current = head;
    while(current){
        Node<T>* next = current->next;
        delete current;
        current = next;
    }
    head = tail = nullptr;
}

}

int main(int argc , char ** argv){
    MySTL::list<int> myList;
    myList.push_back(1);
    myList.push_back(2);
    myList.push_back(3);
    std::cout << "Front: " << myList.front() << std::endl; // Output: 1
    std::cout << "Back: " << myList.back() << std::endl; // Output: 3
    std::cout << "Size: " << myList.size() << std::endl; // Output: 3
    myList.pop_front();
    std::cout << "Front after pop_front: " << myList.front() << std::endl; // Output: 2
    myList.pop_back();
    std::cout << "Back after pop_back: " << myList.back() << std::endl; // Output: 2
    
    myList.push_front(1);
    myList.push_front(0);

    for(auto x : myList){

        std::cout << x << " ";
    }
    std::cout << std::endl;

    std::reverse(myList.begin(), myList.end());

    for(auto x : myList){

        std::cout << x << " ";
    }
    std::cout << std::endl;
    
    return 0;
}