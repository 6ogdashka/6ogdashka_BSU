#include <unistd.h>
#include <thread>
#include <iostream>
#include <vector>
#include <chrono>

bool compare(double a, double b) {
    std::this_thread::sleep_for(std::chrono::milliseconds(7));
    return a < b;
}

void MinMax(const std::vector<double>& vec, size_t& min_idx, size_t& max_idx) {
    if (vec.empty()) return;
    
    min_idx = 0;
    max_idx = 0;
    
    for ( size_t i{1}; i < vec.size(); i+=2 ) {
        if ( !compare(vec[i], vec[i-1]) ) {
            if ( !compare(vec[i], vec[max_idx]) ) {
                max_idx = i;
            }
            if ( compare(vec[i-1], vec[min_idx]) ) {
                min_idx = i - 1;
            }
        } else {
            if ( !compare(vec[i-1], vec[max_idx]) ) {
                max_idx = i - 1;
            }
            if ( compare(vec[i], vec[min_idx]) ) {
                min_idx = i;
            }
        }
    }

    if ( vec.size() % 2 != 0 ) {
        size_t last_idx = vec.size() - 1;
        if ( !compare(vec[last_idx], vec[max_idx]) ){
            max_idx = last_idx;
        }
        if ( compare(vec[last_idx], vec[min_idx]) ) {
            min_idx = last_idx;
        }
    }
    
    std::cout << "Минимальный: " << vec[min_idx] << std::endl;
    std::cout << "Максимальный: " << vec[max_idx] << std::endl;
}

void sum(double& a, double b) {
    std::this_thread::sleep_for(std::chrono::milliseconds(12));
    a += b;
}

void Average(const std::vector<double>& vec, double& result) {
    if(vec.empty()) return;

    result = 0;
    for ( double i : vec) {
        sum(result, i);
    }
    result /= vec.size();
    std::cout << "Среднее арифметическое: " << result << std::endl;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n{};
    std::cin >> n;

    std::vector<double> vec(n);
    for ( int i{};i < n; i++) {
        std::cin >> vec[i];
    }

    size_t min{}, max{};
    double averege_result{};

    std::thread min_max(MinMax, std::ref(vec), std::ref(min), std::ref(max));
    std::thread average(Average, std::ref(vec), std::ref(averege_result));

    min_max.join();
    average.join();

    vec[min] = averege_result;
    vec[max] = averege_result;

    std::cout << "Измененный массив: ";
    for ( double i : vec) {
        std::cout << i << " ";
    }

    return 0;
}
