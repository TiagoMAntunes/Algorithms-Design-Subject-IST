#ifndef LIST_H
#define LIST_H

#include "item.h"

typedef struct node {
    Item item;
    struct node * next;
} * Node;

/*******************************************************************************
 * create_node
 * Input: Pointer to item
 * Output: Pointer to node of list
 *******************************************************************************
*/
Node create_node(Item i);

/******************************************************************************* 
 * free_node
 * Input: Pointer to node
 * Output: void
 * Frees node pointed by n
 *******************************************************************************
*/
void free_node(Node n);

/******************************************************************************* 
 * insert
 * Input: Pointer to head of list
 *		  Poiter to node
 * Output: void
 * Inserts node pointed by new at beginning of list pointed by head
 *******************************************************************************
*/
void insert(Node head, Node new);


#endif