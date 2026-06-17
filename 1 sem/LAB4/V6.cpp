#include <iostream>
#include <random>

void cin_vec(std::vector<int>& vec); 

int main() {

    size_t n;
    std::cin >> n;
    std::vector<int> vec(n);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distrib(-10000000,1000000);
    for ( int i; i <n; ++i) {
        vec[i] = distrib(gen);
    }
    cin_vec(vec);
    for ( int i; i < n; i+=2) {
        vec.erase(vec.begin()+i);
    }
    cin_vec(vec);
}

void cin_vec(std::vector<int>& vec) {
    for ( int i : vec) {
        std::cout << i << " ";
    }
    std::cout << "\n";
}