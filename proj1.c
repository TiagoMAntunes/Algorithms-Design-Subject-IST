#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "lib/item.h"
#include "lib/list.h"


Net read_input(char* filename) {

	FILE *fp = fopen(filename, 'r');
	if (fp == NULL) {
		fprintf(stderr,"Error opening file.");
	}

	int N, M, i;
	if (scanf(fp, &N) != 1) {
		fprintf(stderr,"Error reading file.");
	}

	scanf(fp, i);
	if (scanf(fp, &M) != 1) {
		fprintf(stderr,"Error reading file.")
	}
	scanf(fp, i);

	Net net = net_alloc(N, M);

	for (i = 0; i < M; i++) {
		int u;
		int v;
		if (scanf(fp, &u) != 1 || scanf(fp, &v) != 1) {
			fprintf(stderr, "Error reading file.")
		}
		add_connection(net, atoi(u), atoi(v));
	}

	return net;
}