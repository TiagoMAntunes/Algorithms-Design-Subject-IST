#include "net.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

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
	net->_routers_matrix = (int *) malloc(sizeof(int) * n * n);
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
	//printf("Position: %d\n", get_validated_index(n,x,y));
	return n->_routers_matrix[get_validated_index(n,x,y)]; 
}


void net_add_connection(Net net, int u, int v) {
	net_update_value(net, u, v, 1);
	net_update_value(net, v, u, 1);
}

void net_remove_connection(Net net, int u, int v) {
	net_update_value(net, u, v, 0);
	net_update_value(net, v, u, 0);
}
