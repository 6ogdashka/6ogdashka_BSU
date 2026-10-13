#include <iostream>

int main() {
    int t{};
    std::cin >> t;
    for ( int i{}; i < t; i++) {
        int n,s,f{};
        std::cin >> n >> s >> f;
        if ( n % 2 == 0) {
            std::cout << std::min(n-abs(f-s),abs(f-s)) << "\n";
        } else {
            std::cout << std::min(n+1-abs(f - s),abs(f - s)) << "\n";
        }
    }
    return 0;
}