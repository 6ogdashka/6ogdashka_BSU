#include <iostream>
#include <cmath>
#include "russian.h"
double get_positive_value ();

int main() {
    try {
    setRussianLocale();
    const double kPi = 3.1415927;
    double S;
    std::cout << "Введите площадь круга S: ";
    S = get_positive_value();

    double R = std::sqrt(S / kPi);
    double D = 2 * R;
    double L = 2 * kPi * R;

    std::cout << "Диаметр D: " << D << "\n";
    std::cout << "Длина окружности L: " << L << "\n";
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