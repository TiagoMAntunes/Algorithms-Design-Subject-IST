#include "net.h"
#include "item.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#define CONNECT 	1
#define DISCONNECT 	0

Net net_alloc(int n) {
	Net net = (Net) malloc(sizeof(struct net));
	if (!net) {
		fprintf(stderr, "Error with malloc.");
	}

	net->_n_routers = n; //number of vertexs
	net->_routers_vec = create_vector(n);

	for (int i = 0; i < n; i++) 
		vector_set(net->_routers_vec, i, create_item(i+1));

	//Matrix is just made of ints
	net->_routers_matrix = (int *) calloc(n*n, sizeof(int));
	if (!net->_routers_matrix) {
		fprintf(stderr, "Error with malloc.");
	}
	return net;
}

int get_validated_index(Net n, int u, int v) {
	u--; v--;
	return n->_n_routers * u + v;
}

void net_update_value(Net n, int x, int y, int val) {
	n->_routers_matrix[get_validated_index(n,x,y)] = val;
}

int net_get_value(Net n, int x, int y) {
	return n->_routers_matrix[get_validated_index(n,x,y)]; 
}


void net_add_connection(Net net, int u, int v) {
	net_update_value(net, u, v, CONNECT);
	net_update_value(net, v, u, CONNECT);

	Vector routers = net->_routers_vec;
	// u and v are the nodes' ids, hense the -1
	add_in(vector_at(routers, u-1));
	add_in(vector_at(routers, v-1));
}

void net_remove_connection(Net net, int u, int v) {
	net_update_value(net, u, v, DISCONNECT);
	net_update_value(net, v, u, DISCONNECT);
}

void delete_net(Net n) {
	free(n->_routers_matrix);
	delete_vector(n->_routers_vec, delete_item);
	free(n);
}

void get_adjacents(Net net, Item item, Vector adjs) {
	int N = net->_n_routers;
	int count_adjs = 0;

	for (int i = 0; i < N; i++) {
		if (count_adjs != item->_in && net_get_value(net, item->_id, i+1) == CONNECT) {
			vector_insert(adjs, count_adjs, vector_at(net->_routers_vec, i));
			count_adjs++;
		}
	}
}