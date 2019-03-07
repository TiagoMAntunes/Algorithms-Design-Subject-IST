#include "vector.h"
#include <stdlib.h>

#define BASE_SIZE 8;

Vector create_vector() {
    Vector v = malloc(sizeof(struct vector_t));
    v->_capacity = BASE_SIZE;
    v->_num_elements = 0;
    v->_item_array = malloc(sizeof(Item) * v->_capacity);
    return v;
}

Item vector_at(Vector v, int i) {
    return v->_item_array[i]; //if out of index, returns null
}

int vector_size(Vector v) {
    return v->_num_elements;
}

int vector_empty(Vector v) {
    return v->_num_elements == 0;
}

int vector_capacity(Vector v) {
    return v->_capacity;
}

void vector_validate_size(Vector v) {
    if (v->_num_elements == v->_capacity) {
        v->_item_array = realloc(v->_item_array, sizeof(Item) * v->_capacity * 2);
        v->_capacity *= 2;
    }
}

void vector_push_back(Vector v, Item val) {
    v->_item_array[v->_num_elements++] = val;
    vector_validate_size(v);
}

Item vector_pop(Vector v) {
    v->_num_elements--;
    Item i = v->_item_array[v->_num_elements];
    v->_item_array[v->_num_elements] = NULL;
    return i;
}

void vector_insert(Vector v, int index, Item val) {
    for (int j = v->_capacity-1; j > index; j--)
        v->_item_array[j] = v->_item_array[j-1]; //shifts all to the right
    v->_item_array[index] = val;
    v->_num_elements++;
    vector_validate_size(v);
}

void delete_vector(Vector v, void (*f)()) {
    for (int i = 0; i < v->_num_elements; i++)
        f(vector_at(v, i));
    free(v->_item_array);
    free(v);
}