#include "item.h"
#include <stdio.h>

#define NIL	-1

Item create_item(int id)
{
    Item i = malloc(sizeof(struct item_t));
    i->_id = id;
    i->_pi = NIL;
    return i;
}

void delete_item(Item i) {
    free(i);
}

int item_id_sort(void * voida, void * voidb) {
    Item a = *((Item*) voida);
    Item b = *((Item*) voidb);
    return a->_id - b->_id;
}

int get_id(Item i) {
    return i->_id;
}