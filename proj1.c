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
#define MAX -2
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

int DFS_visit(Net net, int id, int low[], int do_it, int *d, int *pi, char *colors, int *biggest) {
	time++;
	d[id-1] = time;
	colors[id - 1] = GRAY;
    low[id - 1] = time;
	Node adjs_vector;
	int children = 0;

	adjs_vector = get_adjacents(net, id);		
	int val = id;
	Node h;
	for (h = adjs_vector->next; h != NULL; h = h->next) {
		
		int next_id = get_item(h);

		if (colors[next_id - 1] == WHITE) {
			children++;
			pi[next_id-1] = id;
			int tmp = DFS_visit(net, next_id, low, do_it, d, pi, colors, biggest);
			if (tmp > val) val = tmp;

            low[id - 1] = MIN(low[id - 1], low[next_id - 1]);   

	        /*  u is not root and low of one of its children is more than u's or u is root and has 2 or more children */
	        if (do_it && colors[id-1] != YELLOW && ((pi[id-1] != NIL && low[next_id -1] >= d[id -1]) || (pi[id-1] == NIL && children > 1))){
	        	colors[id-1] = YELLOW;
	           	net_add_art_point(net);
	        }

		} else if (next_id != pi[id-1]) { /* if the vertex isn't where it came from */
            low[id -1] = MIN(low[id - 1], d[next_id -1]);
        }

	}
	if (do_it && colors[id-1] != YELLOW) {
		colors[id-1] = BLACK;
	}
	time++;
	if (pi[id-1] == NIL && colors[id-1] != YELLOW && (time - d[id-1]) / 2 + 1 > *biggest)
		*biggest = (time - d[id-1]) / 2 + 1;
	return val;
}

int counter = 0;

void DFS(Net net, int do_it, int *d, int *pi, char * colors, int * biggest) {
	int i, N = net->_n_routers;
    int low[N];
 
	for (i = 0; i < N; i++) {	
		if (do_it || (!do_it && colors[i] != YELLOW)) {	
			colors[i] = WHITE;
		}
		d[i] = NIL;
		pi[i] = NIL;
		low[i] = NIL;
	}

	time = 0;
	for (i = N-1; i > -1; i--) {		
		if (colors[i] == WHITE && do_it) {
			int tmp = DFS_visit(net, i+1, low, do_it, d, pi, colors, biggest);
			pi[tmp-1] = MAX;
			counter++;
		} else if (colors[i] == WHITE){
			DFS_visit(net, i+1, low, do_it, d, pi, colors, biggest);
		}
	}
}

int num_cmp(void * a, void * b) {
	return *((int*)a) - *((int*)b);
}



int main() {
	int biggest_size = 0;
	Net net = read_input();   
	int d[net->_n_routers];
	int pi[net->_n_routers];
	char colors[net->_n_routers];
	DFS(net,JUSTDOIT, d, pi, colors, &biggest_size);
	biggest_size = 0;
	

	printf("%d\n", counter);
	/* Id's of subnets */
	int i=0;
	if (counter > 0)
		for (i = 0; (i < net->_n_routers) && (pi[i] != MAX); i++);
	
	printf("%d", ++i);
	for (;i < net->_n_routers; i++) {
		if (pi[i] == MAX)
			printf(" %d", i+1);
	}
	printf("\n");

	/* Number of points that are dangerous */
	printf("%d\n", net_get_N_art_points(net));
	
	DFS(net,DONTDOIT, d,pi, colors, &biggest_size);
	
	
	/* Biggest size of sub net */
	printf("%d\n", biggest_size);
	
	
	/* clean up */
    delete_net(net);

	return 0;
}