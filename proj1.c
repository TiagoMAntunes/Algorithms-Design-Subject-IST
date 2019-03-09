#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "lib/item.h"
#include "lib/net.h"


#define NIL		-1
#define CONNECTED	1
#define MIN(A, B) ((A) < (B) ? (A) : (B))

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

void DFS_visit(Net net, Item u, int low[]) {
	time++;
	u->_d = time;
	u->_color = GRAY;
    low[u->_id - 1] = time;
	Vector adjs_vector = create_vector(u->_in);

	get_adjacents(net, u, adjs_vector);

	for (int i = 0; i < u->_in; i++) {
		Item v = vector_at(adjs_vector,i);
		if (v->_color == WHITE) {
			v->_pi = u->_id;
			DFS_visit(net, v, low);
            low[u->_id - 1] = MIN(low[u->_id - 1], low[v->_id - 1]);
            if (low[v->_id - 1] > u->_d)
                printf("PONTE ENCONTRADA. IDS: %d para %d\n", u->_id, v->_id);
            //it's supposed to happen something in the if above
		} else if (v->_id != u->_pi) { //if the vertex isn't where it came from
            low[u->_id -1] = MIN(low[u->_id - 1], v->_d);
        }
	}
	u->_color = BLACK;
	time++;
	u->_f = time;

    delete_vector(adjs_vector, NULL);
}

void DFS(Net net) {
	int i, N = net->_n_routers;
	Item* items = net->_routers_vec->_item_array;
    int low[N];
    
    for (i = 0; i < N; i++){
        low[i] = NIL;
    }

	for (i = 0; i < N; i++) {
		items[i]->_color = WHITE;
		items[i]->_pi = NIL;
	}

	time = 0;
	for (i = 0; i < N; i++) {
		if (items[i]->_color == WHITE) {
			DFS_visit(net, items[i], low);
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

	Item* items = net->_routers_vec->_item_array; //Not relevant here but improve abstraction


	for (int i = 0; i < n; i++) {
		Item u = items[i];
		printf("d = %d, f = %d, pi = %d\n", u->_d, u->_f, u->_pi);
	}

	printf("====\n");
    delete_net(net);
	return 0;
}