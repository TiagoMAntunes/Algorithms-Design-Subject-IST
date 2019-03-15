#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "lib/item.h"
#include "lib/net.h"


#define NIL		-1
#define CONNECTED	1
#define MIN(A, B) ((A) < (B) ? (A) : (B))
#define JUSTDOIT 1
#define DONTDOIT 0
#define YELLOW 	3
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

int DFS_visit(Net net, Item u, int low[], int do_it) {
	time++;
	u->_d = time;
	u->_color = GRAY;
    low[u->_id - 1] = time;
	Vector adjs_vector;
	int i, children = 0;

	adjs_vector = get_adjacents(net, u);		
	int val = u->_id;
	for (i = 0; i < vector_size(adjs_vector); i++) {		
		Item v = vector_at(adjs_vector,i);

		if (v->_color == WHITE) {
			children++;
			v->_pi = u->_id;
			int tmp = DFS_visit(net, v, low, do_it);
			if (tmp > val) val = tmp;

            low[u->_id - 1] = MIN(low[u->_id - 1], low[v->_id - 1]);   

	        /*  u is not root and low of one of its children is more than u's */
	        if (do_it && u->_pi != NIL && low[v->_id -1] >= u->_d) {
	        	u->_color = YELLOW;
	           	net_add_art_point(net, u);
	        }
        
            /*  u is root and has 2 or more children */
	        if (do_it && u->_pi == NIL && children > 1) {
	        	u->_color = YELLOW;
	          	net_add_art_point(net, u);
	         }

		} else if (v->_id != u->_pi) { /* if the vertex isn't where it came from */
            low[u->_id -1] = MIN(low[u->_id - 1], v->_d);
        }

	}
	if (do_it && u->_color != YELLOW) {
		u->_color = BLACK;
	}
	time++;
	u->_f = time;

	return val;
}



Vector DFS(Net net, int do_it) {
	int i, N = net->_n_routers;
	Item* items = net->_routers_vec->_item_array;
    int * low = calloc(sizeof(int),N);
	Vector subnets_maxs = create_vector(1);
 
	for (i = 0; i < N; i++) {	
		if (do_it || (!do_it && items[i]->_color != YELLOW)) {	
			items[i]->_color = WHITE;
		}

		items[i]->_pi = NIL;
		low[i] = NIL;
	}

	time = 0;
	for (i = 0; i < N; i++) {		
		if (items[i]->_color == WHITE) {
			vector_push_back(subnets_maxs, create_item(DFS_visit(net, items[i], low, do_it)));
		}
	}
	free(low);
	return subnets_maxs;
}


void print_results(Vector subnets_net, Net net, int biggest_size) {
	int i;
	/* Number of subnets */
	printf("%d\n", vector_size(subnets_net));
	/* Id's of subnets */
	vector_sort(subnets_net, item_id_sort);
	for (i = 0; i < vector_size(subnets_net); i++) {
		printf("%d ", vector_at(subnets_net, i)->_id);
	}
	printf("\n");
	delete_vector(subnets_net, delete_item);

	/* Number of points that are dangerous */
	printf("%d\n", net_get_N_art_points(net));
	/* Biggest size of sub net */
	printf("%d", biggest_size);
}


int main() {
	int i, biggest_size = 0;
	Net net = read_input();   
	Vector subnets_net = DFS(net,JUSTDOIT);
//	printf("First DFS done\n");
	/*  build new net without the ap's and do the DFS */
	//Net new_net = net_create_remove_articulations(net);
	//printf("Updated graph\n");

	delete_vector(DFS(net,DONTDOIT), delete_item);
	//printf("Second DFS done\n");
	for (i = 0; i < net->_n_routers; i++) {		
		Item item = vector_at(net->_routers_vec,i);
		if (item->_pi == NIL && item->_color != YELLOW)
			if ((item->_f / 2) - item->_d + 1 > biggest_size)
				biggest_size = (item->_f / 2) - item->_d + 1;
	}
//	printf("Found the data needed\n");
	print_results(subnets_net, net, biggest_size);

	/* clean up */
    delete_net(net);
	/*delete_net(new_net);
	*/

	return 0;
}