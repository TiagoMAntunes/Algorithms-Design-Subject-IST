#include "item.h"

Item create_item(int j)
{
    Item i = malloc(sizeof(struct item_t));
    i->j = j;
    return i;
}

void delete_item(Item i) {
    free(i);
}