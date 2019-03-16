#include "vector.h"
#include "list.h"

#ifndef NET_H
#define NET_H
typedef struct net {
	int _n_routers;
	Node * _routers_matrix;
	int _articulation_points;
} * Net;


Net net_alloc(int vertexs);
int net_get_value(Net n, int x, int y);
void net_update_value(Net n, int x, int y);
void net_add_connection(Net net, int u, int v);
void net_remove_connection(Net net, int u, int v);
void delete_net(Net n);
Node get_adjacents(Net net, int item);
void net_add_art_point(Net net);
int net_get_N_art_points(Net net);

#endif