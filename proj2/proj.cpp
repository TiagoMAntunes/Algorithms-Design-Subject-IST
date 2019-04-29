#include <iostream>

class Edge{
        int _weight;
        int _target;
    public:
        Edge(int weight, int target);
        int getWeight() { return _weight; }
        int getTarget() { return _target; }
};

Edge::Edge(int weight, int target) {
    _weight = weight;
    _target = target;
}

int main() {
    //parse input
    int f, e, t;    
    int prod;
    int cap;
    int o, d, c;
    std::cin >> f >> e >> t;
    
    while (f-- > 0)
        std::cin >> prod;
        
    while (e-- > 0)
        std::cin >> cap;

    while (t-- > 0) 
        std::cin >> o >> d >> c;



    return 0;
}