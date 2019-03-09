#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "lib/item.h"
#include "lib/net.h"


Net read_input(char* filename) {

	FILE *fp = fopen(filename, "r");
	if (fp == NULL) {
		fprintf(stderr,"Error opening file.");
	}

	int N, M, i;
	if (fscanf(fp, "%d", &N) != 1) {
		fprintf(stderr,"Error reading file.");
	}

	if (fscanf(fp, "%d", &M) != 1) {
		fprintf(stderr,"Error reading file.");
	}

	Net net = net_alloc(N);

	for (i = 0; i < M; i++) {
		int u;
		int v;
		if (fscanf(fp, "%d", &u) != 1 || fscanf(fp, "%d", &v) != 1) {
			fprintf(stderr, "Error reading file.");
		}
		net_add_connection(net, u, v);
	}

	return net;
}



int main() {
	Net net = read_input("ex2.txt");

	int n = net->_n_routers;

	for (int i = 1; i <= n; i++) {
		for (int j = i + 1; j <= n; j++) {

			if (net_get_value(net, i, j) == 1) {
				printf("%d %d\n", i, j);
			} 
		}
	}
	return 0;
}