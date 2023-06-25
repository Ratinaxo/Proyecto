#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "vector.h"

typedef struct Vector Vector;

struct Vector{
    void **data;
    int size;
    int capacity;
    int head;
    int tail;
};

Vector *createVector(int size){
    Vector *new = (Vector *)malloc(sizeof(Vector));
    assert(new != NULL);
    new->data = (void **)malloc(sizeof(void *)*size);
    assert(new->data != NULL);
    new->size = 0;
    new->capacity = size;
    new->head = 0;
    new->tail = 0;
    return new;
}

void resizeVector(Vector *vector, int newSize){
    vector->data = (void **)realloc(vector->data, sizeof(void *)*newSize);
    vector->capacity = newSize;
    if (vector->size > vector->capacity){
        vector->size = vector->capacity;
    }
}

void appendVector(Vector* vector, void* data){
    if (vector->size == vector->capacity){
        resizeVector(vector, vector->capacity*2);
    }
    vector->data[vector->tail] = data;
    vector->tail = (vector->tail+1)%vector->capacity;
    vector->size++;
}

void *getVector(Vector* vector, int index){
    if(index >= vector->size){
        return NULL;
    }
    return vector->data[(vector->head+index)%vector->capacity];
}

void * setVector(Vector* vector, int index, void* data){
    if(index >= vector->size){
        return NULL;
    }
    vector->data[(vector->head+index)%vector->capacity] = data;
}

void shuffleVector(Vector *vector){
    for (int i = 0; i < vector->size; i++){
        int index = rand() % vector->size;
        void *aux = getVector(vector, i);
        setVector(vector, i, getVector(vector, index));
        setVector(vector, index, aux);
    }
}

void *destroyVector(Vector* vector){
    free(vector->data);
    free(vector);
}