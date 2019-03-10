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
	int children = 0;

	get_adjacents(net, u, adjs_vector);

	for (int i = 0; i < u->_in; i++) {
		Item v = vector_at(adjs_vector,i);
		if (v->_color == WHITE) {
			children++;
			v->_pi = u->_id;
			DFS_visit(net, v, low);

            low[u->_id - 1] = MIN(low[u->_id - 1], low[v->_id - 1]);   

	        // v is not root and low of one of its children is more that v's
	        if (u->_pi != NIL && low[v->_id -1] >= u->_d) {
	           	net_add_art_point(net, u->_id - 1, u);
	        }
        
            // v is root and has 2 or more children
	        if (u->_pi == NIL && children > 1) {
	          	net_add_art_point(net, u->_id - 1, u);
	         }

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
    
 
	for (i = 0; i < N; i++) {
		items[i]->_color = WHITE;
		items[i]->_pi = NIL;
		low[i] = NIL;
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
	int i;

	DFS(net);
	int subnets = net_count_subnets(net);

	// build new net without the ap's and do the DFS
	Vector points = net_get_art_points(net);
	Net new_net = net_create_remove_articulations(net);
	DFS(new_net);

	int biggest_size = 0;
	for (int i = 0; i < new_net->_n_routers; i++) {
		Item item = vector_at(new_net->_routers_vec,i);
		if (item->_pi == NIL)
			if ((item->_f / 2) - item->_d + 1 > biggest_size)
				biggest_size = (item->_f / 2) - item->_d + 1;
	}

	
	printf("%d\n", subnets);
	printf("XXX\n");
	printf("%d\n", net_get_N_art_points(net));
	printf("XXX\n");
	printf("Biggest size: %d\n", biggest_size);

	//clean up
    delete_net(net);
	delete_net(new_net);
	return 0;
}