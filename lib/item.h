#ifndef __ITEM_H
#define __ITEM_H

#include <stdlib.h>
#define WHITE	0
#define GRAY	1
#define BLACK	2

typedef struct item_t {
    int _id, _pi;
    short _color;
} * Item;

Item create_item(int id);
void delete_item(Item i);
int item_id_sort(void* a, void* b);
int get_id(Item i);
#endif