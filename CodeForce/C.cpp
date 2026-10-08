#include <algorithm>
#include <map>
#include <cstddef>
#include <iostream>
#include <vector>

int main() {

    int t{};
    std::cin >> t;

    for ( int i{}; i < t; i++) {
        std::size_t n{};
        std::cin >> n;
        std::vector<int> vec(n);
        for ( int j{}; j < n; j++) {
            std::cin >> vec[j];
        }
        std::map<long long,int> result{};
        for ( int j{}; j < n-4;j++) {
            int k = vec[j]+vec[j+2]+vec[j+4];
            if ((j != result[k]) && ((j != result[k]+2) && (j != result[k]+4))) {
                
            }
        }
        for ( int j{}; j < t.size(); j++) {

        }


    }
    return 0;
}