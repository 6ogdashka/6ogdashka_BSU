#include <cmath>
#include <iostream>

int Antie(double n) {
    if ( n > (int)n ) {
        return (int)(n + 1);
    } return (int)n;
}

int main() {
    int t;
    std::cin >> t;
    
    for ( int i{}; i < t; i++) {
        double n;
        std::cin >> n;
        int m {Antie(sqrt(n))};
        std::cout << m << "\n";
        int l = n-((m-1)*(m-1));
        for ( int j{}; j < m-1; j++) {
            for ( int k{}; k < m-1; k++) {
                std::cout << "#";
            }
            if ( l > 0) {
                std::cout << "#";
                --l;
            } else {
                std::cout << ".";
            }
            std::cout << "\n";
        }
        for ( int j{}; j < m; j++) {
            if ( l > 0) {
                std::cout << "#";
                l--;
            } else std::cout << ".";
        }
        std::cout << "\n";
    }

}