#ifndef VECTOR_H
#define VECTOR_H
#include <stdlib.h>
typedef struct Vector {
    int size;
    int *v;
    int capacity;
} Vector;

Vector init_vector(int);
void push_back(Vector * , int);

#endif // VECTOR_H