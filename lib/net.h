//#include "list.h"
#include "vector.h"

#ifndef NET_H
#define NET_H
typedef struct net {
	int _n_routers;
	Vector _routers_vec;
	int * _routers_matrix;
} * Net;


Net net_alloc(int vertexs);
int net_get_value(Net n, int x, int y);
void net_update_value(Net n, int x, int y, int val);
void net_add_connection(Net net, int u, int v);
void net_remove_connection(Net net, int u, int v);
void delete_net(Net n);
#endif