#include <iostream>

int main() {
    int t;
    std::cin >> t;

    for (int i{}; i < t;i++) {
        std::string str{};
        std::string result{"NO"};
        std::cin >> str;
        if ( str.length() >= 3) {
        for ( int j{0}; j < str.length()-2; j ++) {
            if ( str[j] == str[j+2]) {
                result = "YES";
                break;
            }
        }
        }
        std::cout << result << "\n";
        str.clear();
        result.clear();
    }
}