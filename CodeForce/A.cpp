#include <iostream>

int main() {

    int t{};
    std::cin >> t;

    int x,y,r;

    for ( int i{}; i < t; i++) {
        std::cin >> x >> y >> r;
        std::cout << x-r << " " << y << "\n";
    }
}