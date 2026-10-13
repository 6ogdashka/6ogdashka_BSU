#include <iostream>
#include <string>

std::string returnDeleted(std::string a, std::string b) {
    std::string result;
    for ( char i : a) {
        if (b.find(i) == std::string::npos) {
            result+=i;
        }
    }
    return result;
}


int main() {
    std::string first_str{"abcdefghijklmnopqrstuvwxyz"};
    std::string current{};
    current = first_str;
    std::string prev_str{};
    std::cout << current << "\n"; // 1    26
    prev_str = current;
    std::cout.flush();
    current.clear();
    std::cin >> current;
    current = returnDeleted(prev_str,current);
    char last = current[current.size()-1];
    current.pop_back();
    std::cout << current << "\n"; // 2    12
    prev_str = current;
    std::cout.flush();
    current.clear();
    std::cin >> current;
    current = returnDeleted(prev_str,current);
    std::cout << current << "\n"; // 3    6
    prev_str = current;
    std::cout.flush();
    current.clear();
    std::cin >> current;
    current = returnDeleted(prev_str,current);
    current +=last;
    std::cout << current << "\n"; // 4     4
    prev_str = current;
    std::cout.flush();
    current.clear();
    std::cin >> current;
    current = returnDeleted(prev_str,current);
    std::cout << current << "\n"; //5     2
    prev_str = current;
    std::cout.flush();
    current.clear();
    std::cin >> current;
    current = returnDeleted(prev_str,current);
    std::cout << "! " << current; // вывод
    std::cout.flush();
    return 0;
}