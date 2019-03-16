#include "net.h"
#include "item.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#define CONNECT 	1
#define DISCONNECT 	0
#define NIL			-1

Net net_alloc(int n) {
	Net net = (Net) malloc(sizeof(struct net));
	if (!net) {
		fprintf(stderr, "Error with malloc.");
	}

	net->_n_routers = n; /* number of vertexs */
	net->_routers_vec = create_vector(n);
	net->_articulation_points = 0;

	int i;
	/* Creates all vertexs */
	for (i = 0; i < n; i++) {
		vector_set(net->_routers_vec, i, create_item(i+1));
	}


	/* Abstraction using list of adjacencies */
	net->_routers_matrix = (Vector *) malloc(n * sizeof(Vector));
	if (!net->_routers_matrix) {
		fprintf(stderr, "Error with malloc allocating %d.", n*n);
	}
	for (i = 0; i < n; i++){
		net->_routers_matrix[i] = create_vector(8);
	}
	return net;
}

int get_validated_index(Net n, int u, int v) {
	u--; v--;
	return n->_n_routers * u + v;
}

void net_update_value(Net n, int x, int y) {
	vector_push_back(n->_routers_matrix[--x], vector_at(n->_routers_vec,--y));
}

int net_get_value(Net n, int x, int y) {
	return DISCONNECT;
}


void net_add_connection(Net net, int u, int v) {
	net_update_value(net, u, v);
	net_update_value(net, v, u);

	Vector routers = net->_routers_vec;
	/* u and v are the nodes' ids, hense the -1 */
	add_in(vector_at(routers, u-1));
	add_in(vector_at(routers, v-1));
}

void net_remove_connection(Net net, int u, int v) {
	net_update_value(net, u, v);
	net_update_value(net, v, u);
}

void delete_net(Net n) {
	int i;
	for (i = 0; i < n->_n_routers; i++)
		delete_vector(n->_routers_matrix[i], NULL);
	delete_vector(n->_routers_vec, delete_item);
	free(n->_routers_matrix);
	free(n);
}

Vector get_adjacents(Net net, Item item) {
	return net->_routers_matrix[item->_id-1];
}

void net_add_art_point(Net net) {
	net->_articulation_points++;
}

int net_get_N_art_points(Net net) {
	return net->_articulation_points;
}

Vector net_get_items(Net net) {
	return net->_routers_vec;
}

int net_count_subnets(Net net) {
	Vector items = net_get_items(net);
	int i, subnets = 0;
	int n = net->_n_routers;

	for (i = 0; i < n; i++) {
		Item u = vector_at(items,i);
		if (u->_pi == NIL) {
			subnets++;
		}
	}
	return subnets;
}