#include <iostream>
#include <forward_list>
#include <array>

#define YELLOW 3
#define GRAY 2
#define WHITE 0
#define BLACK 1

#define NIL -1
#define MAX_NET -3

#define DOIT true
#define DONTDOIT false

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

bool do_it = false;
int time_count;
int counter = 0;
int art_points = 0;
int DFS_visit(std::forward_list<int> *edges, int N, int current_id, int *low, int *starts, int *pi, char *colors, int *biggest)
{
    time_count++;
    starts[current_id - 1] = time_count;
    colors[current_id - 1] = GRAY;
    low[current_id - 1] = time_count;
    std::forward_list<int> curr_adjs = edges[current_id - 1];
    int children = 0;
    int val = current_id;

    for (int next_id : curr_adjs)
    {
        if (colors[next_id - 1] == WHITE)
        {
            children++;
            pi[next_id - 1] = current_id;
            int tmp = DFS_visit(edges, N, next_id, low, starts, pi, colors, biggest);
            val = MAX(val, tmp);

            low[current_id - 1] = MIN(low[current_id - 1], low[next_id - 1]);

            if (do_it && colors[current_id - 1] != YELLOW && ((pi[current_id - 1] != NIL && low[next_id - 1] >= starts[current_id - 1]) || (pi[current_id - 1] == NIL && children > 1)))
            {
                colors[current_id - 1] = YELLOW;
                art_points++;
            }
        }
        else if (next_id != pi[current_id - 1])
            low[current_id - 1] = MIN(low[current_id - 1], starts[next_id - 1]);
    }
    if (do_it && colors[current_id - 1] != YELLOW)
        colors[current_id - 1] = BLACK;
    time_count++;
    if (pi[current_id - 1] == NIL && colors[current_id - 1] != YELLOW && (time_count - starts[current_id - 1]) / 2 + 1 > *biggest)
        *biggest = (time_count - starts[current_id - 1]) / 2 + 1;
    return val;
}

void DFS(std::forward_list<int> *edges, int *starts, int *pi, char *colors, int *biggest, int N)
{
    int i;
    int * low = new int[N];
    //initialization
    for (i = 0; i < N; i++)
    {
        if (do_it || (!do_it && colors[i] != YELLOW))
            colors[i] = WHITE;
        starts[i] = NIL;
        pi[i] = NIL;
        low[i] = NIL;
    }
    time_count = 0;
    for (i = N - 1; i > -1; i--)
    {
        if (colors[i] == WHITE && do_it)
        {
            int tmp = DFS_visit(edges, N, i + 1, low, starts, pi, colors, biggest);
            pi[tmp - 1] = MAX_NET;
            counter++;
        }
        else if (colors[i] == WHITE)
        {
            DFS_visit(edges, N, i + 1, low, starts, pi, colors, biggest);
        }
    }
    delete[] low;
}

int main()
{
    int N, M, i;
    if (scanf("%d", &N) != 1)
    {
        fprintf(stderr, "Error reading input.");
    }

    if (scanf("%d", &M) != 1)
    {
        fprintf(stderr, "Error reading input.");
    }

    std::forward_list<int> *edges = new std::forward_list<int>[N];

    //inserts edges in array
    for (i = 0; i < M; i++)
    {
        int u;
        int v;
        if (scanf("%d", &u) != 1 || scanf("%d", &v) != 1)
        {
            fprintf(stderr, "Error reading file.");
        }
        edges[u - 1].push_front(v);
        edges[v - 1].push_front(u);
    }
    do_it = DOIT;
    int *starts = (int *)malloc(sizeof(int) * N), *pi = (int *)malloc(sizeof(int) * N);
    char colors[N];
    int biggest = 0;

    DFS(edges, starts, pi, colors, &biggest, N);

    std::cout << counter << std::endl;
    if (counter > 0)
        for (i = 0; (i < N) && (pi[i] != MAX_NET); i++)
            ;

    printf("%d", ++i);
    for (; i < N; i++)
    {
        if (pi[i] == MAX_NET)
            printf(" %d", i + 1);
    }
    printf("\n");

    std::cout
        << art_points << std::endl;
    biggest = 0;
    do_it = DONTDOIT;

    DFS(edges, starts, pi, colors, &biggest, N);
    std::cout << biggest << std::endl;

    free(starts);
    free(pi);
    delete[] edges;
    return 0;
}