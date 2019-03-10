#include "vector.h"
#include <stdlib.h>

Vector create_vector(int n) {
    Vector v = malloc(sizeof(struct vector_t));
    v->_capacity = n;
    v->_num_elements = 0;
    v->_item_array = malloc(sizeof(Item) * v->_capacity);
    for (int i = 0; i < n; i++)
        v->_item_array[i] = NULL;
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

void vector_add_at(Vector v, int index, Item val) {
    if (v->_item_array[index] == NULL) {
        v->_item_array[index] = val;
        v->_num_elements++;
    }
}

void vector_set(Vector v, int index, Item val) {
    if (v->_item_array[index])
        delete_item(v->_item_array[index]);
    else
        v->_num_elements++;
    v->_item_array[index] = val;
}

void delete_vector(Vector v, void (*f)()) {
    if (f != NULL)
        for (int i = 0; i < v->_num_elements; i++)
            f(vector_at(v, i));
    free(v->_item_array);
    free(v);
}

Item* vector_get_items(Vector v) {
    return v->_item_array;
}