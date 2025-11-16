#include <iostream>
#include "russian.h"

void task17();

int main() {
    try {
    std::cout << "Задача 17: Простые несократимые дроби\n\n";
    task17();
    } catch ( const char* msg) { std::cout << msg; }
    return 0;
}

void task17() {
    setRussianLocale();
    std::cout << "=== Задача 17: Простые несократимые дроби между 0 и 1 ===\n";  
    int max_denominator;
    std::cout << "Введите максимальный знаменатель: ";
    std::cin >> max_denominator;

    if (max_denominator < 2) {
        throw "Знаменатель должен быть не меньше 2\n\n";
    }
    int a = 0, b = 1;
    int c = 1, d = max_denominator;
    int counter {};
    while (c <= max_denominator) {
        ++counter;
        int k = (max_denominator + b) / d;
        int next_a = c;
        int next_b = d;
        int next_c = k * c - a;
        int next_d = k * d - b;
        if (c > 0 && c < d && d <= max_denominator) {
            std::cout << "Дробь:" << counter << ": " << c << "/" << d << "\n";
        }
        
        a = next_a;
        b = next_b;
        c = next_c;
        d = next_d;
    }
}