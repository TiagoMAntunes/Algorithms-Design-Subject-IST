#include <iostream>

#define SOURCE 1

class Edge{
        int _weight;
        int _target;
    public:
        int getWeight() { return _weight; }
        int getTarget() { return _target; }
        int setWeight(int weight) { _weight = weight; }
        int setTarget(int target) { _target = target; }
};

int f, e, t;

int transformID(int id) {
    if (id >= 2 && id <= f + 1) {
        //do some logic
    } else if (id > f + 1) {
        //do some logic
    }
}

int main() {
    //parse input
    int prod;
    int cap;
    int o, d, c;
    std::cin >> f >> e >> t;

    Edge * edges = new Edge[2 + f * 2 + e * 2]; //source + target + 2 * suppliers + 2 * stations

    while (f-- > 0)
        std::cin >> prod;
        
    while (e-- > 0)
        std::cin >> cap;

    while (t-- > 0) 
        std::cin >> o >> d >> c;

    delete[] edges;
    return 0;
}