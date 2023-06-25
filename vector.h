#ifndef Vector_h
#define Vector_h


typedef struct Vector Vector;

Vector *createVector(int size);

void resizeVector(Vector* vector, int newSize);

void appendVector(Vector* vector, void* data);

void * getVector(Vector* vector, int index);

void * setVector(Vector* vector, int index, void* data);

void shuffleVector(Vector* vector);

void * destroyVector(Vector* vector);


#endif /* VECTOR.H */