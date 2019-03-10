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

	net->_n_routers = n; //number of vertexs
	net->_routers_vec = create_vector(n);
	net->_articulation_points = create_vector(n);

	for (int i = 0; i < n; i++) {
		vector_set(net->_routers_vec, i, create_item(i+1));
	}


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
	delete_vector(n->_articulation_points, NULL);
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

void net_add_art_point(Net net, int i, Item item) {
	//vector_add_at(net->_articulation_points, i, item);
	if (vector_at(net->_articulation_points,i) == NULL)
		vector_set(net->_articulation_points,i, item);
}

int net_get_N_art_points(Net net) {
	return vector_size(net->_articulation_points);
}

Vector net_get_art_points(Net net) {
	return net->_articulation_points;
}

Vector net_get_items(Net net) {
	return net->_routers_vec;
}

int net_count_subnets(Net net) {
	Vector items = net_get_items(net);
	int subnets = 0;
	int n = net->_n_routers;

	for (int i = 0; i < n; i++) {
		Item u = vector_at(items,i);
		if (u->_pi == NIL) {
			subnets++;
		}
	}
	return subnets;
}

Net net_create_remove_articulations(Net net) {
	Net new_net = net_alloc(net->_n_routers - vector_size(net->_articulation_points));
	int count_articulations = 0;

	for (int i = 0; i < net->_n_routers; i++) {
		if (vector_at(net->_articulation_points, i) == NULL) {
			//not an articulation point, add normally
			int tmp = 0;
			for (int j = i; j < net->_n_routers; j++) { 
				//because it's undirected, we just need to add from the diagonal to the front reducing the time that is needed
				if (vector_at(net->_articulation_points, j) == NULL && net->_routers_matrix[net_get_value(net, i+1,j+1)] != DISCONNECT)
					net_add_connection(new_net, i - count_articulations + 1, j - tmp + 1);
				else if (vector_at(net->_articulation_points, j))
					tmp++;
			}
		} else {
			//articulation point, just increment and ignore
			count_articulations++;
		}
	}
	return new_net;

}