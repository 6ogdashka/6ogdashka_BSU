#include <cstring>
#include <iostream>
#include <cstdlib>
#include <random>
#include <string>
#include <type_traits>



const std::string kAlphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";



int main() {
    std::string s('a', 2);
    for (uint32_t state = 0; state < 0x7fffffff; state++) {
        std::srand(state);
        for (int j = 0; j < 2;j++) {
            s[j] = kAlphabet[std::rand() % kAlphabet.size()];
        }
        if (s == "NL") {
            std::cout << state << '\n';
            return 0;
        }
    }
    // std::cout << s2 << '\n';
}