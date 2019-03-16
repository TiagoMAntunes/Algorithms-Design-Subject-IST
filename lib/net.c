#include "net.h"
#include "item.h"
#include "list.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#define CONNECT 	1
#define DISCONNECT 	0
#define NIL			-1

Net net_alloc(int n) {
	int i;
	Net net = (Net) malloc(sizeof(struct net));
	if (!net) {
		fprintf(stderr, "Error with malloc.");
	}

	net->_n_routers = n; /* number of vertexs */
	net->_articulation_points = 0;
	/* Abstraction using list of adjacencies */
	net->_routers_matrix = (Node *) malloc(n * sizeof(Node));
	if (!net->_routers_matrix) {
		fprintf(stderr, "Error with malloc allocating %d.", n*n);
	}
	for (i = 0; i < n; i++){
		net->_routers_matrix[i] = list_create_node(0);
	}
	return net;
}

int get_validated_index(Net n, int u, int v) {
	u--; v--;
	return n->_n_routers * u + v;
}

/*void net_update_value(Net n, int x, int y) {
	vector_push_back(n->_routers_matrix[--x], vector_at(n->_routers_vec,--y));
}
*/

int net_get_value(Net n, int x, int y) {
	return DISCONNECT;
}



void net_add_connection(Net net, int u, int v) {
	/*net_update_value(net, u, v);
	net_update_value(net, v, u); */

	/* u and v are the nodes' ids, hense the -1 */
	Node* adj_list = net->_routers_matrix;
	Node new_u = list_create_node(u);
	Node new_v = list_create_node(v);

	list_insert(adj_list[u-1], new_v);
	list_insert(adj_list[v-1], new_u);
}


/*void net_remove_connection(Net net, int u, int v) {
	net_update_value(net, u, v);
	net_update_value(net, v, u);
}*/

void delete_net(Net n) {
	int i;
	for (i = 0; i < n->_n_routers; i++)
		list_delete(n->_routers_matrix[i]);
	free(n->_routers_matrix);
	free(n);
}

Node get_adjacents(Net net, int item) {
	return net->_routers_matrix[item-1];
}

void net_add_art_point(Net net) {
	net->_articulation_points++;
}

int net_get_N_art_points(Net net) {
	return net->_articulation_points;
}