#include "net.h"
#include <stdio.h>

#define N 3

void print_connections(Net n) {
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            printf("%d ", net_get_value(n, i + 1, j + 1));
        printf("\n");
    }
}

int main()
{
    Net n = net_alloc(N);
    net_add_connection(n, 1, 2);
    net_add_connection(n, 2, 3);
    printf("Connections:\n");
    print_connections(n);
    printf("--------\n");
    net_remove_connection(n, 1,2);
    print_connections(n);

}