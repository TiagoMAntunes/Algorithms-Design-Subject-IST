#ifndef __ITEM_H
#define __ITEM_H

#include <stdlib.h>

typedef struct item_t {
    int j;
} * Item;

Item create_item(int j);
void delete_item(Item i);

#endif