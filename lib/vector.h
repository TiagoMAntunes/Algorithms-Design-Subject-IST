#ifndef __VECTOR_H
#define __VECTOR_H

#include "item.h"
typedef struct vector_t {
    int * _item_array;
    int _capacity;
    int _num_elements;
} * Vector;

/* Constructor */
Vector create_vector(int n); /* returns an empty vector with a base size; */

/* Accessors */
int vector_at(Vector v, int i); /* returns the value at that position */
int vector_size(Vector v); /* returns the current number of elements inserted */
int vector_empty(Vector v); /* evaluates if it's empty */
int vector_capacity(Vector v); /* returns the current capacity of a vector */

/* Modifiers */
void vector_push_back(Vector v, int val); /* inserts at the end the value val */
int vector_pop(Vector v); /* removes and returns the last element */
void vector_insert(Vector v, int index, int val); /* inserts a value in an index */
void vector_set(Vector v, int indeex, int val);
void vector_sort(Vector v, int (*key)());
/* Deconstructor */
void delete_vector(Vector v);
int* vector_get_items(Vector v);
int vector_contains(Vector contains, int item);
void vector_remove(Vector v, int index);
#endif