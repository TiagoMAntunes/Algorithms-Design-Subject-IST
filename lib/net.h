#include "vector.h"

#ifndef NET_H
#define NET_H
typedef struct net {
	int _n_routers;
	Vector _routers_vec;
	Vector * _routers_matrix;
	Vector _articulation_points;
} * Net;


Net net_alloc(int vertexs);
int net_get_value(Net n, int x, int y);
void net_update_value(Net n, int x, int y);
void net_add_connection(Net net, int u, int v);
void net_remove_connection(Net net, int u, int v);
void delete_net(Net n);
Vector get_adjacents(Net net, Item item);
void net_add_art_point(Net net, Item item);
int net_get_N_art_points(Net net);
Vector net_get_art_points(Net net);
int net_count_subnets(Net net);
Net net_create_remove_articulations(Net net);
#endif