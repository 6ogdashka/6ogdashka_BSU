#include <algorithm>
#include <cstddef>
#include <iostream>
#include <vector>
#include <string>

int main() {

    int t{};
    std::cin >> t;
    for ( int i{}; i < t; i++) {
        std::size_t n{};
        std::cin >> n;
        std::string commands;
        std::cin >> commands;
        std::vector<int> q{};
        std::vector<int> p{};

        for (int k{1}; k <= n; k++) {
            int command = commands[k-1] - '0';
            if ( command == 3 ) {
                continue;
            }
            if ( command == 1) {
                q.push_back(k);
            } else if ((command == 2) && (q.empty())){
                continue;
            } else {
                q.pop_back();
                p.push_back(k);
            }
        }
        std::vector<int> result(q.size()+p.size());
        std::merge(q.begin(),q.end(),p.begin(),p.end(),result.begin());
        std::cout << result.size() << "\n";
        for ( int k{}; k < result.size(); k++) {
            std::cout << result[k] << "\n";
        }
        q.clear();
        p.clear();
        result.clear();
        commands.clear();
    }
    return 0;
}