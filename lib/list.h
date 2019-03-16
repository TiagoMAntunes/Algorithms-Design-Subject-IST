#ifndef __LIST_H
#define __LIST_H

#include "item.h"

typedef struct node {
    int item;
    struct node * next;
} * Node;

int get_item(Node n);

/*******************************************************************************
 * createNode
 * Input: Pointer to process
 * Output: Pointer to node of list
 *******************************************************************************
*/
Node list_create_node(int i);

/******************************************************************************* 
 * freeNode
 * Input: Pointer to node
 * Output: void
 * Frees node pointed by p
 *******************************************************************************
*/
void list_free_node(Node n);

/******************************************************************************* 
 * insert
 * Input: Pointer to head of list
 *		  Poiter to node
 * Output: void
 * Inserts node pointed by new at beginning of list pointed by head
 *******************************************************************************
*/
void list_insert(Node head, Node new);


/******************************************************************************* 
 * freeAll
 * Input: Pointer to head of list to free
 * Output: void
 *******************************************************************************
*/
void list_delete(Node head);

/******************************************************************************* 
 * next
 * Input: Pointer to node
 * Output: Pointer to node next to h
 *******************************************************************************
*/
Node next(Node h);

#endif

