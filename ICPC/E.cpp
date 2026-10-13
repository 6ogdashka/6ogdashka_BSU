#include <climits>
#include <iostream>
#include <string>
#include <vector>

int main() {
    int t;
    std::cin >> t;

    for ( int i{}; i < t; i++) {
        int n;
        std::cin >> n;
        std::string result{"YES"};
        long long even{LONG_LONG_MIN};
        long long odd{LONG_LONG_MIN};
        for ( int j{}; j < n; j++) {
            int buff{};
            std::cin >> buff;
            if ( buff % 2 == 0) {
                if ( buff < odd) {
                    result = "NO";
                } else {
                    odd = buff;
                }
            } else {
                if ( buff < even) {
                    result = "NO";
                } else {
                    even = buff;
                }
            }
        }
        std::cout << result << "\n";
    }
}
