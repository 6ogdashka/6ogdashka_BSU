#include <unistd.h>
#include <thread>
#include <iostream>
#include <vector>
#include <chrono>
#include <dlfcn.h>

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

    std::cout << "Исходный массив: ";
    for ( double i : vec) {
        std::cout << i << " ";
    }
    std::cout << "\n";

    size_t min{}, max{};
    double averege_result{};

    void* handle = dlopen("so/MinMax.so", RTLD_LAZY);
    auto* MinMax = (void (*)(const std::vector<double>&, size_t&, size_t&))dlsym(handle, "MinMax");

    std::thread min_max(MinMax, std::ref(vec), std::ref(min), std::ref(max));
    std::thread average(Average, std::ref(vec), std::ref(averege_result));

    min_max.join();
    average.join();

    dlclose(handle);

    vec[min] = averege_result;
    vec[max] = averege_result;

    std::cout << "Измененный массив: ";
    for ( double i : vec) {
        std::cout << i << " ";
    }

    return 0;
}
