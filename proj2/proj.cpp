#include <iostream>
#include <forward_list>
#include <limits>
#define SOURCE 0
#define TARGET 1
#define MIN(A,B) ((A) < (B) ? (A) : (B))

class Edge{
        int _capacity;
        int _target;
        int _flux;
    public:
        int getCapacity() { return _capacity; }
        int getTarget() { return _target; }
        int getFlux() { return _flux; }
        void setFlux(int v) { _flux = v; }
        void increaseFlux(int n) { _flux += n; }
        int residualCapacity() { return _capacity - _flux;}
        Edge(int w, int t);
};

Edge::Edge(int w, int t) {
    _capacity = w;
    _target = t;
    _flux = 0;
}

int f, e;

int validate_index(int id) {
    if (id > f+1)
        id += e;
    return id;
}

void push(int u, int v, int * overflows, Edge * edge) {
    int available_flux = MIN(overflows[u], edge->residualCapacity());
    edge->increaseFlux(available_flux);
    overflows[u] -= available_flux;
    overflows[v] += available_flux;
}

void relabel(int u, std::forward_list<Edge*>& edges, int * heights) {
    int min_height = std::numeric_limits<int>::max();
    for (auto t : edges)
        if (t->residualCapacity() > 0 && heights[t->getTarget()] < min_height)
            min_height = heights[t->getTarget()];
    heights[u] = 1 + min_height;
}

void initialize_pre_flow(int max, int * overflows, int * heights, std::forward_list<Edge*>* edges_list) {
    for (int i = 0; i < max; i++) {
        overflows[i] = 0;
        heights[i] = 0;
    }

    for (int i = 0; i < max; i++)
        for (auto edge : edges_list[i])
            edge->setFlux(0);
    
    heights[0] = max;

    for (auto edge : edges_list[0]) {
        edge->setFlux(edge->getCapacity());
        overflows[edge->getTarget()] = edge->getCapacity();
        overflows[0] -= edge->getCapacity();
    }
}

void discharge(int u, int * overflows, int * heights, std::forward_list<Edge*>& edges) {
    while (overflows[u] > 0){
        for (auto edge : edges) {
            if (edge->residualCapacity() > 0 && heights[u] == heights[edge->getTarget()] + 1)
                push(u, edge->getTarget(), overflows, edge);
        }
        if (overflows[u] > 0)
            relabel(u, edges, heights);
    }
}

void relabel_to_front(std::forward_list<Edge *>* edges, int max, int * overflows, int * heights) {
    initialize_pre_flow(max, overflows, heights, edges);
    std::forward_list<int> * L = new std::forward_list<int>(max - 2);
    for (int i = max-1; i > 1; i--) L->push_front(i);
    std::forward_list<int>::iterator it = L->begin();
    int u;
    while(it != L->end()) {
        u = *it;
        int oldh = heights[u];
        discharge(u, overflows, heights, edges[u]);
        if (heights[u] > oldh) {
            L->remove(u);
            L->push_front(u);
            it = L->begin();
        }
        it++;
    }
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
        edges[SOURCE].push_front(new Edge(prod, index));
        edges[index].push_front(new Edge(prod, SOURCE));
        index++;
    }
    counter = e;
    while (counter-- > 0) {
        std::cin >> cap;
        edges[index].push_front(new Edge(cap,index + e));
        edges[index + e].push_front(new Edge(cap,index));
        index++;
    }

    while (t-- > 0) {
        std::cin >> o >> d >> c;
        edges[validate_index(o)].push_front(new Edge(c,d));
        edges[d].push_front(new Edge(c,validate_index(o)));
    }

    int * overflows = new int[2 +f + e*2];
    int * heights = new int[2 +f + e*2];
    relabel_to_front(edges, 2 + f + e * 2, overflows, heights);

    //just for debugging
    /*
    for (int i = 0; i < 2 + f + e * 2; i++) {
        std::cout << "------------Analyzing " << i  << std::endl;
        for (auto edge : edges[i])
            std::cout << i << " to " << edge->getTarget() << " flux=" << edge->getFlux() << " capacity=" << edge->getCapacity() << std::endl;
    }*/

    for (int i = 0; i < 2 + f + e * 2; i++) {
        for (auto edge : edges[i])
            delete edge;
    }
    delete[] edges;
    return 0;
}