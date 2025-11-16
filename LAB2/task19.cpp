#include <cmath>
#include <iostream>
#include "russian.h"

void task19();

int main() {
    try {
        setRussianLocale();
        std::cout << "Задача 19: Пифагоровы тройки\n\n";
        task19();
    } catch (const char* msg) { 
        std::cout << msg; 
    }
    return 0;
}

void task19() {
    std::cout << "=== Задача 19: Пифагоровы тройки чисел ===\n";
    
    int n;
    std::cout << "Введите наибольшее значение для стороны прямоугольного треугольника: ";
    std::cin >> n;

    if (n < 1) {
        throw "N должно быть натуральным числом (N >= 1)\n\n";
    }

    int triple_count = 0;
    for (int a = 1; a <= n; ++a) {
        for (int b = a; b <= n; ++b) {
            const long long sum_of_squares = 
                static_cast<long long>(a) * a + static_cast<long long>(b) * b;
            const int potential_c = static_cast<int>(std::sqrt(sum_of_squares));
            
            if (potential_c <= n && 
                static_cast<long long>(potential_c) * potential_c == sum_of_squares &&
                potential_c > b) {
                ++triple_count;
                std::cout << "Пифагорова тройка №" << triple_count << ": (" 
                          << a << ", " << b << ", " << potential_c << ")\n";
            }
        }
    }
    
    if (triple_count == 0) {
        throw "Пифагоровых троек не найдено\n\n";
    }
}