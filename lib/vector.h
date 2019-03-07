#ifndef __VECTOR_H
#define __VECTOR_H

#include "item.h"
typedef struct vector_t {
    Item * _item_array;
    int _capacity;
    int _num_elements;
} * Vector;

//Constructor
Vector create_vector(); //returns an empty vector with a base size;

//Accessors
Item vector_at(Vector v, int i); //returns the value at that position
int vector_size(Vector v); //returns the current number of elements inserted
int vector_empty(Vector v); //evaluates if it's empty
int vector_capacity(Vector v); //returns the current capacity of a vector

//Modifiers
void vector_push_back(Vector v, Item val); //inserts at the end the value val
Item vector_pop(Vector v); //removes and returns the last element
void vector_insert(Vector v, int index, Item val); //inserts a value in an index

//Deconstructor
void delete_vector(Vector v, void (*item_free_function)());

#endif