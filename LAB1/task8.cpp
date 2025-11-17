#include <iostream>
#include <cmath>
#include "russian.h"
double get_positive_value ();

int main() {
    try {
    setRussianLocale();
    std::cout << "Введите координаты вершин треугольника (x1, y1, x2, y2, x3, y3): ";
    double x1 = get_positive_value();
    double y1 = get_positive_value();
    double x2 = get_positive_value();
    double y2 = get_positive_value();
    double x3 = get_positive_value();
    double y3 = get_positive_value();
    double a = std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2));
    double b = std::sqrt(std::pow(x3 - x2, 2) + std::pow(y3 - y2, 2));
    double c = std::sqrt(std::pow(x1 - x3, 2) + std::pow(y1 - y3, 2));

    double perimeter = a + b + c;
    double p = perimeter / 2;
    double area = std::sqrt(p * (p - a) * (p - b) * (p - c));

    std::cout << "Периметр: " << perimeter << "\n";
    std::cout << "Площадь: " << area << "\n";
    } catch ( const char* msg) { std::cout << msg;}
    return 0;
}

double get_positive_value () {
    double value;
    if (( std::cin >> value ) && ( value > 0)) {
        return value;
    } else {
        throw " Число должно быть положительным ";
    }
}