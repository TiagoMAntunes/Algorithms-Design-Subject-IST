#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "lib/item.h"
#include "lib/net.h"


#define NIL		-1
#define WHITE	0
#define GRAY	1
#define BLACK	2
#define CONNECTED	1

int time;

Net read_input() {

	int N, M, i;
	if (scanf("%d", &N) != 1) {
		fprintf(stderr,"Error reading input.");
	}

	if (scanf("%d", &M) != 1) {
		fprintf(stderr,"Error reading input.");
	}

	Net net = net_alloc(N);

	for (i = 0; i < M; i++) {
		int u;
		int v;
		if (scanf("%d", &u) != 1 || scanf("%d", &v) != 1) {
			fprintf(stderr, "Error reading file.");
		}
		net_add_connection(net, u, v);
	}

	return net;
}

void get_adjacents(Net net, Item item, Vector adjs) {
	int N = net->_n_routers;
	int count_adjs = 0;
	Item* items = net->_routers_vec->_item_array;

	for (int i = 0; i < N; i++) {
		if (count_adjs != item->_in && net_get_value(net, item->_id, i+1) == CONNECTED) {
			vector_insert(adjs, count_adjs, items[i]);
			count_adjs++;
		}
	}
}


void DFS_visit(Net net, Item u) {
	time++;
	u->_d = time;
	u->_color = GRAY;

	Vector adjs_vector = create_vector(u->_in);
	Item* adjs = adjs_vector->_item_array;

	get_adjacents(net, u, adjs_vector);

	for (int i = 0; i < u->_in; i++) {
		Item v = adjs[i];
		if (v->_color == WHITE) {
			v->_pi = u->_id;
			DFS_visit(net, v);
		}
	}
	u->_color = BLACK;
	time++;
	u->_f = time;

	free(adjs);
}

void DFS(Net net) {
	int i, time, N = net->_n_routers;
	Item* items = net->_routers_vec->_item_array;

	for (i = 0; i < N; i++) {
		items[i]->_color = WHITE;
		items[i]->_pi = NIL;
	}

	time = 0;
	for (i = 0; i < N; i++) {
		if (items[i]->_color == WHITE) {
			DFS_visit(net, items[i]);
		}
	}
}


int main() {
	Net net = read_input();

	int n = net->_n_routers;

	for (int i = 1; i <= n; i++) {
		for (int j = i + 1; j <= n; j++) {

			if (net_get_value(net, i, j) == 1) {
				printf("%d %d\n", i, j);
			} 
		}
	}
	printf("====\n");

	DFS(net);

	Item* items = net->_routers_vec->_item_array;

	for (int i = 0; i < n; i++) {
		Item u = items[i];
		printf("d = %d, f = %d, pi = %d\n", u->_d, u->_f, u->_pi);
	}

	printf("====\n");

	return 0;
}