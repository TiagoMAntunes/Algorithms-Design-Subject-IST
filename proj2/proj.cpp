#include <iostream>

int main() {
    //parse input
    int f, e, t;    
    std::cin >> f >> e >> t;
    
    while (f-- > 0) {
        int prod;
        std::cin >> prod;
        std::cout << prod;
    }
    std::cout << std::endl;
    while (e-- > 0) {
        int cap;
        std::cin >> cap;
        std::cout << cap;
    }
    std::cout << std::endl;
    while (t-- > 0) {
        int o, d, c;
        std::cin >> o >> d >> c;
        std::cout << o << d << c;
    std::cout << std::endl;
    }
    return 0;
}