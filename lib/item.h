#ifndef __ITEM_H
#define __ITEM_H

#include <stdlib.h>
#define WHITE	0
#define GRAY	1
#define BLACK	2

typedef struct item_t {
    int _id, _in, _out, _color, _d, _f, _pi, _n_children;
} * Item;

Item create_item(int id);
void delete_item(Item i);
void add_in(Item i);
void add_out(Item i);

#endif