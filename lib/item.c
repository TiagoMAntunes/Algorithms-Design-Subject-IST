#include "item.h"

Item create_item(int id)
{
    Item i = malloc(sizeof(struct item_t));
    i->_id = id;
    i->_in = 0;
    i->_out = 0;
    return i;
}

void delete_item(Item i) {
    free(i);
}