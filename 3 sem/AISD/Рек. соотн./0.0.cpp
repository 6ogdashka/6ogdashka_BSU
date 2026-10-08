#include <iostream>
#include <fstream>
#include <set>
#include <numeric>

int main() {
    std::ifstream input_number("input.txt");
    long long current_number;
    std::set<long long> numbers;
    
    while ( input_number >> current_number ) {
        numbers.insert(current_number);
    }
    
    std::ofstream output("output.txt");
    long long sum{};
    output << std::accumulate(numbers.begin(),numbers.end(),sum);
}