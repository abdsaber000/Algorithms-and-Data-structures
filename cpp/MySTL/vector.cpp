#include <iostream>
#include <algorithm>
#include <assert.h>

namespace MySTL{

template<typename T>    
class IteratorVector : public std::iterator<std::random_access_iterator_tag, T> {
    T* ptr;
public:

    IteratorVector(T* p) : ptr(p) {}
    T& operator*() { return *ptr; }
    IteratorVector& operator++() { ++ptr; return *this; } // Prefix 
    IteratorVector operator++(int) { // Postfix
        IteratorVector temp = *this;
        ++ptr;
        return temp;
    }
    IteratorVector& operator--() { --ptr; return *this; } // Prefix
    IteratorVector operator--(int) { // Postfix
        IteratorVector temp = *this;
        --ptr;
        return temp;
    }
    std::ptrdiff_t operator-(const IteratorVector& other) const { return ptr - other.ptr; }
    IteratorVector operator+(int n) const { return IteratorVector(ptr + n); }
    IteratorVector operator-(int n) const { return IteratorVector(ptr - n); }
    bool operator<(const IteratorVector& other) const { return ptr < other.ptr; }
    bool operator!=(const IteratorVector& other) const { return ptr != other.ptr; }
    bool operator==(const IteratorVector& other) const { return ptr == other.ptr; }
    ~IteratorVector() { ptr = nullptr; } // Destructor to avoid dangling pointer
};


template<typename T>
class vector {
    T* data;
    size_t capacity = 0;
    size_t length = 0;
    void resize(size_t new_capacity);
    
public:
    vector(int n = 0, T default_value = T());
    void push_back(T val);
    void pop_back();
    T& front();
    T& back();
    size_t size();
    T& operator[](size_t index);
    IteratorVector<T> begin() { return IteratorVector<T>(data); }
    IteratorVector<T> end() { return IteratorVector<T>(data + length); }
    ~vector() { delete[] data; } 
};



template<typename T>
vector<T>::vector(int n , T default_value) : capacity(n), length(n) {
    data = new T[capacity];
    for(size_t i = 0; i < length; ++i) {
        data[i] = default_value;
    }
}


template<typename T>
void vector<T>::resize(size_t new_capacity) {
    T* new_data = new T[new_capacity];
    for (size_t i = 0; i < length; ++i) {
        new_data[i] = data[i];
    }
    delete[] data;
    data = new_data;
    capacity = new_capacity;
}

template<typename T>
void vector<T>::push_back(T val) {
    if (length == capacity) {
        resize(capacity * 2);
    }
    data[length++] = val;
}

template<typename T>
void vector<T>::pop_back() {
    if (length > 0) {
        --length;
    }
}

template<typename T>
T& vector<T>::front() {
    if (length > 0) {
        return data[0];
    }
    throw std::out_of_range("Vector is empty");

}

template<typename T>
T& vector<T>::back() {
    if (length > 0) {
        return data[length - 1];
    }
    throw std::out_of_range("Vector is empty");
}

template<typename T>
T& vector<T>::operator[](size_t index) {
    if (index < length) {
        return data[index];
    }
    throw std::out_of_range("Index out of range");
}

template<typename T>
size_t vector<T>::size() {
    return length;
}

}

int main(int argc , char ** argv){
    MySTL::vector<int> v(10);
    for(int i = 0; i < 10; i++){
        v[i] = i;
    }
    for (int i = 0; i < 10; ++i) {
        v.push_back(-i);
    }
    std::cout << "Front: " << v.front() << std::endl;
    std::cout << "Back: " << v.back() << std::endl;
    std::cout << "Size: " << v.size() << std::endl;

    for(size_t i = 0; i < v.size(); i++){
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;

    for(auto x : v){
        std::cout << x << " ";
    }
    std::cout << std::endl;

    std::sort(v.begin(), v.end());

    for(auto x : v){
        std::cout << x << " ";
    }
    std::cout << std::endl;

    auto it = std::find(v.begin(), v.end(), 5);
    assert(it != v.end());
    it = std::find(v.begin(), v.end(), 100);
    assert(it == v.end());

    MySTL::vector<int> v2(5, 1);
    for(auto c : v2)
        std::cout << c << " ";
    std::cout << std::endl;
    return 0;
}