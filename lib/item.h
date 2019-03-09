#ifndef __ITEM_H
#define __ITEM_H

#include <stdlib.h>

typedef struct item_t {
    int _id, _in, _out;
} * Item;

Item create_item(int id);
void delete_item(Item i);



#endif