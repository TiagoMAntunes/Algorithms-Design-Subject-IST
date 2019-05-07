#include <iostream>
#include <forward_list>
#include <limits>
#include <queue>
#define SOURCE 0
#define TARGET 1
#define MIN(A,B) ((A) < (B) ? (A) : (B))
#define WHITE 0
#define BLACK 1

class Edge{
        int _capacity;
        int _target;
        int _flux;
        int _from;
        Edge * _rev;
    public:
        int getCapacity() { return _capacity; }
        int getTarget() { return _target; }
        int getFlux() { return _flux; }
        int getOrigin() {return _from;}
        void setFlux(int v) { _flux = v; }
        void increaseFlux(int n) { _flux += n; }
        int residualCapacity() { return _capacity - _flux;}
        void setReverse(Edge * e) {_rev = e;}
        Edge * getReverse() {return _rev;}
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
    _rev = NULL;
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
    Edge * reverse = edge->getReverse();
    reverse->setFlux(-edge->getFlux());  
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
   
    heights[TARGET] = max;

    for (auto edge : edges_list[TARGET]) {
        edge->setFlux(edge->getCapacity());
        overflows[edge->getTarget()] = edge->getCapacity();
        overflows[TARGET] -= edge->getCapacity();
        Edge* reverse = edge->getReverse();
        reverse->setFlux(-edge->getCapacity());
    }
}

void reset(int i, std::forward_list<Edge *> * edges ) {
    neighbors[i] = edges[i].begin();
}

void discharge(int u, int * overflows, int * heights, std::forward_list<Edge*>* edges, std::queue<int> &Q) {
    while (overflows[u] > 0){
        if (neighbors[u] == edges[u].end()) {
            relabel(u, edges[u], heights);
            reset(u, edges);
        } else if ((*neighbors[u])->residualCapacity() > 0 && heights[u] == heights[(*neighbors[u])->getTarget()] + 1) {
            push(u, (*neighbors[u])->getTarget(), overflows, *neighbors[u], edges[(*neighbors[u])->getTarget()]);
            if ((*neighbors[u])->getTarget() != 1 && (*neighbors[u])->getTarget() != 0) Q.push((*neighbors[u])->getTarget());
        }
        else 
            neighbors[u]++;

    }
}

void relabel_to_front(std::forward_list<Edge *>* edges, int max, int * overflows, int * heights) {
    initialize_pre_flow(max, overflows, heights, edges);

    std::queue<int>Q;
    for (int i = 2; i < max; i++) Q.push(i);
    int u;
    while(!Q.empty() && overflows[TARGET] != -overflows[SOURCE]) {
        u = Q.front();
        Q.pop();
        discharge(u, overflows, heights, edges, Q);  
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
        Edge *reverse = new Edge(SOURCE, 0, index);
        Edge *newEdge = new Edge(index, prod, SOURCE);
        edges[SOURCE].push_front(reverse); //edge from source to supplier
        edges[index].push_front(newEdge); //reverse edge
        newEdge->setReverse(reverse);
        reverse->setReverse(newEdge);
        index++;
        prodTotal += prod;
    }
    counter = e;
    int capTotal = 0;
    while (counter-- > 0) {
        std::cin >> cap;
        Edge * reverse = new Edge(index,0,index + e);
        Edge * newEdge = new Edge(index + e,cap,index);
        edges[index].push_front(reverse); //set capacity of storage as 2 vertexes
        edges[index + e].push_front(newEdge);
        newEdge->setReverse(reverse);
        reverse->setReverse(newEdge);
        index++;
        capTotal += e;
    }

    while (t-- > 0) {
        std::cin >> o >> d >> c;
        Edge * reverse = new Edge(validate_index(o),0,d);
        Edge *newEdge = new Edge(d,c,validate_index(o));
        edges[validate_index(o)].push_front(reverse); //set edges inside graph while validating if origin is storage
        edges[d].push_front(newEdge);
        newEdge->setReverse(reverse);
        reverse->setReverse(newEdge);
    }


    int max = 2 + f + e * 2;
    int * overflows = new int[max];
    int * heights = new int[max];
    neighbors = new std::forward_list<Edge *>::iterator[max];
    for (int i = 0; i < max; i++)
        neighbors[i] = edges[i].begin();
    relabel_to_front(edges, max, overflows, heights);


    std::cout << overflows[SOURCE] << std::endl; // the output
    int findGap[max+1];
    for (int i = 0; i < max; i++) {
    	findGap[i] = -1;
    }
    for (int i = 0; i < max; i++) {
    	if (heights[i] < max) {
    		findGap[heights[i]] = 1;
    	}
    }

    int gap = max;
    for (int i = max-1; i >= 0; i--) {
    	if (findGap[i] == -1){
    		gap = i;
    		break;
    	}
    }
    
    bool changed = false; 
    for (int i = f + 2 + e; i < max; i++) { // for each storage
        int origin = i - e;
        if (heights[i] >= gap && heights[origin] < gap) {
            if (changed)
                std::cout << " ";
            else
                changed = true;
            std::cout << i - e;
        }
    }
    int i;
    std::priority_queue<Edge *, std::vector<Edge*>, Compare> edges1;
    for (i = 2; i < f + 2; i++) { //for each supplier
        for (auto edge : edges[i])
            if (heights[i] < gap && heights[edge->getTarget()] >= gap && edge->getTarget() != 0) //avoid back edges to source
                edges1.push(edge);
    }

    while (!edges1.empty()) {
        Edge * edge = edges1.top();
        std::cout << std::endl;
        std::cout << edge->getOrigin() << " " << edge->getTarget();
        edges1.pop();
    }

    for (i = f + 2 + e; i < max; i++) { //for edges exiting storage
        for (auto edge : edges[i]) 
            if (heights[i] < max && heights[edge->getTarget()] >= max && i - edge->getTarget() != e) //avoid going back to storage
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
    delete[] overflows;
    delete[] heights;
    delete[] neighbors;
    return 0;  
}