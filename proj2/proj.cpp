#include <iostream>
#include <forward_list>
#include <limits>
#include <queue>
#define SOURCE 0
#define TARGET 1
#define MIN(A,B) ((A) < (B) ? (A) : (B))

class Edge{
        int _capacity;
        int _target;
        int _flux;
        int _from;
    public:
        int getCapacity() { return _capacity; }
        int getTarget() { return _target; }
        int getFlux() { return _flux; }
        int getOrigin() {return _from;}
        void setFlux(int v) { _flux = v; }
        void increaseFlux(int n) { _flux += n; }
        int residualCapacity() { return _capacity - _flux;}
        Edge(int s,int w, int t);
};

bool operator<(Edge& lhs, Edge &rhs) {
    return lhs.getOrigin() > rhs.getOrigin() || ( lhs.getOrigin() == rhs.getOrigin() && lhs.getTarget() > rhs.getTarget());
}

class Compare {
    public:
        bool operator() (Edge * a, Edge * b) {
            return *a < *b;
        }
};

Edge::Edge(int s,int w, int t) {
    _capacity = w;
    _target = t;
    _flux = 0;
    _from = s;
}

int f, e;
std::forward_list<Edge *>::iterator * neighbors;

int validate_index(int id) {
    if (id > f+1)
        id += e;
    return id;
}

void push(int u, int v, int * overflows, Edge * edge, std::forward_list<Edge *>& edges) {
    int available_flux = MIN(overflows[u], edge->residualCapacity());
    edge->increaseFlux(available_flux);
    for (auto new_edge : edges) //update back edge
        if (new_edge->getTarget() == u){
            new_edge->setFlux(-edge->getFlux());
            break;
        }    
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
    
    heights[TARGET] = max;

    for (auto edge : edges_list[TARGET]) {
        edge->setFlux(edge->getCapacity());
        overflows[edge->getTarget()] = edge->getCapacity();
        overflows[TARGET] -= edge->getCapacity();
        for (auto new_edge : edges_list[edge->getTarget()])
            if (new_edge->getTarget() == TARGET) {
                new_edge->setFlux(-edge->getCapacity());
                break;
            }
    }
}

void reset(int i, std::forward_list<Edge *> * edges ) {
    neighbors[i] = edges[i].begin();
}

void discharge(int u, int * overflows, int * heights, std::forward_list<Edge*>* edges) {
    while (overflows[u] > 0){
        if (neighbors[u] == edges[u].end()) {
            relabel(u, edges[u], heights);
            reset(u, edges);
        } else if ((*neighbors[u])->residualCapacity() > 0 && heights[u] == heights[(*neighbors[u])->getTarget()] + 1) 
            push(u, (*neighbors[u])->getTarget(), overflows, *neighbors[u], edges[(*neighbors[u])->getTarget()]);
        else 
            neighbors[u]++;

    }
}

void relabel_to_front(std::forward_list<Edge *>* edges, int max, int * overflows, int * heights) {
    initialize_pre_flow(max, overflows, heights, edges);
/* DEBUG 
    for (int i = 0; i < 2 + f + e * 2; i++) {
        std::cout << "------------Analyzing PRE FLOW " << i  << std::endl;
        for (auto edge : edges[i])
            std::cout << i << " to " << edge->getTarget() << " flux=" << edge->getFlux() << " capacity=" << edge->getCapacity() << std::endl;
    }
*/
    std::forward_list<int> * L = new std::forward_list<int>(max - 2); 
    for (int i = 2; i < max; i++) L->push_front(i);
    std::forward_list<int>::iterator it = L->begin();
    int u;
    while(it != L->end() && overflows[TARGET] != -overflows[SOURCE]) {
        u = *it;
        int oldh = heights[u];

      //  int e = overflows[u]; //==============

        discharge(u, overflows, heights, edges);
        if (heights[u] > oldh) {
            L->remove(u);
            L->push_front(u);
            it = L->begin();
        }
    /* DEBUG    
        std::cout << "v = " << *it << ", oldh = " << oldh << ", h = " << heights[*it] << ", e[v] = " << e << std::endl;
    */    
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
    int prodTotal = 0;
    while (counter-- > 0){
        std::cin >> prod;
        edges[SOURCE].push_front(new Edge(SOURCE, prod, index));
        edges[index].push_front(new Edge(index, prod, SOURCE));
        index++;
        prodTotal += prod;
    }
    counter = e;
    int capTotal = 0;
    while (counter-- > 0) {
        std::cin >> cap;
        edges[index].push_front(new Edge(index,cap,index + e));
        edges[index + e].push_front(new Edge(index + e,cap,index));
        index++;
        capTotal += e;
    }

    while (t-- > 0) {
        std::cin >> o >> d >> c;
        edges[validate_index(o)].push_front(new Edge(validate_index(o),c,d));
        edges[d].push_front(new Edge(d,c,validate_index(o)));
    }


    int max = 2 + f + e * 2;
    int * overflows = new int[max];
    int * heights = new int[max];
    neighbors = new std::forward_list<Edge *>::iterator[max];
    for (int i = 0; i < max; i++)
        neighbors[i] = edges[i].begin();
    relabel_to_front(edges, max, overflows, heights);

    //just for debugging
    /*
    for (int i = 0; i < max; i++) {
        std::cout << "------------Analyzing " << i  << std::endl;
        for (auto edge : edges[i])
            std::cout << i << " to " << edge->getTarget() << " flux=" << edge->getFlux() << " capacity=" << edge->getCapacity() << std::endl;
    }

    std::cout << "=== Analyzing Heights" << std::endl;
    for (int i = 0; i < max; i++) {
        std::cout << "h[" << i << "] = " << heights[i] << std::endl;
    }
    */
    //std::cout << "=== Results ===" << std::endl;
    std::cout << overflows[SOURCE] << std::endl;

 /*   std::cout << "prodTotal = " << prodTotal << std::endl;
    std::cout << "capTotal = " << capTotal << std::endl;
    std::cout << "flux = " << overflows[SOURCE] << std::endl;
*/
    bool changed = false; 
    for (int i = f + 2 + e; i < max; i++) {
        int origin = i - e;
        if (heights[i] >= max && heights[origin] < max) {
            if (heights[i] >= max && heights[origin] < max) {
                if (changed)
                    std::cout << " ";
                else
                    changed = true;
                std::cout << i - e;
            }
        }
    }
    int i;
    std::priority_queue<Edge *, std::vector<Edge*>, Compare> edges1;
    for (i = 2; i < f + 2; i++) {
        for (auto edge : edges[i])
            if (heights[i] < max && heights[edge->getTarget()] >= max && edge->getTarget() != 0)
                edges1.push(edge);
    }

    while (!edges1.empty()) {
        Edge * edge = edges1.top();
        std::cout << std::endl;
        std::cout << edge->getOrigin() << " " << edge->getTarget();
        edges1.pop();
    }

    for (i = f + 2 + e; i < max; i++) {
        for (auto edge : edges[i]) 
            if (heights[i] < max && heights[edge->getTarget()] >= max)
                edges1.push(edge);
    }

    while (!edges1.empty()) {
        Edge * edge = edges1.top();
        std::cout << std::endl;
        std::cout << edge->getOrigin() - e << " " << edge->getTarget();
        edges1.pop();
    }
    std::cout << std::endl;

    for (int i = 0; i < 2 + f + e * 2; i++) {
        for (auto edge : edges[i])
            delete edge;
    }
    delete[] edges;
    return 0;  
}