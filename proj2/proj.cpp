#include <iostream>
#include <forward_list>
#define SOURCE 0
#define TARGET 1
#define MIN(A,B) ((A) < (B) ? (A) : (B))

class Edge{
        int _weight;
        int _target;
        int _flux;
    public:
        int getWeight() { return _weight; }
        int getTarget() { return _target; }
        int getFlux() { return _flux; }
        Edge(int w, int t);
};

Edge::Edge(int w, int t) {
    _weight = w;
    _target = t;
    _flux = 0;
}

int f, e;

int validateIndex(int id) {
    if (id > f+1)
        id += e;
    return id;
}

int main() {
    //parse input
    int prod;
    int cap;
    int t;
    int o, d, c;
    int counter;
    std::cin >> f >> e >> t;

    std::forward_list<Edge *> * edges = new std::forward_list<Edge *>[2 + f + e * 2]; //source + target + suppliers + 2 * stations
    //source is 0
    //target is 1
    int index = 2;
    counter = f;
    while (counter-- > 0){
        std::cin >> prod;
        edges[SOURCE].push_front(new Edge(prod, index++));
    }
    counter = e;
    while (counter-- > 0) {
        std::cin >> cap;
        edges[index].push_front(new Edge(cap,index + e));
        index++;
    }

    while (t-- > 0) {
        std::cin >> o >> d >> c;
        edges[validateIndex(o)].push_front(new Edge(c,d));
    }

    for (int i = 0; i < 2 + f + e * 2; i++) {
        for (auto edge : edges[i])
            delete edge;
    }
    delete[] edges;
    return 0;
}