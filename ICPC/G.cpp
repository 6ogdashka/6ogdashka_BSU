#include <iostream>
#include <unordered_map>
#include <vector>

std::vector<int> CountSort(std::vector<int>& numb, int MAX) {
    std::vector<int> count(MAX+1,0);
    for ( int i{}; i < numb.size(); i++) {
        count[numb[i]]++;
    }
    std::vector<int> result{};
    int i{};
    while ( i < count.size()) {
        if ( count[i] != 0) {
            result.push_back(i);
            count[i]--;
        } else {
            i++;
        }
    }
    return result;
}


int main() {
    int t;
    std::cin >> t;

    for ( int i{}; i < t; i++) {
        
    }
}