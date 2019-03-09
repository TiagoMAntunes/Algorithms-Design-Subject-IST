#ifndef NET_H
#define NET_H


#include "list.h"

typedef struct net {
	int n_routers;
	int n_connections;
	Node* routers;
} * Net;


Net net_alloc(int n, int m);
void add_connection(Net net, int u, int v);

#endif