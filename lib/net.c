#include "net.h"
#include "list.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

Net net_alloc(int n, int m) {
	Net net = (Net) malloc(sizeof(struct net));
	if (!net) {
		fprintf(stderr, "Error with malloc.");
	}

	net->n_routers = n;
	net->n_connections = m;

	net->routers = (Node*) malloc(sizeof(struct node*) * n);
	if (!net->routers) {
		fprintf(stderr, "Error with malloc.");
	}

	return net;
}

void add_connection(Net net, int u, int v) {
	Node new = create_node(create_item(v));
	insert(net->routers[u-1], new);
}