#include "vector.h"

Vector init_vector(int size){
    Vector v;
    v.v = (int *)malloc(sizeof(int) * size);
    v.capacity = size;
    v.size = 0;
    return v;
}

static void expand(Vector * v){
    v->capacity *= 2;
    v->v = realloc(v->v , sizeof(int) * v->capacity);
}

void push_back(Vector * v , int val){
    if(v->size == v->capacity)
        expand(v);
    
    v->v[v->size++] = val;
}