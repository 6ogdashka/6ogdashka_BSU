#include <iostream>
#include "russian.h"
double get_positive_value ();

int main() {
    try {
    setRussianLocale();
    const double kPi = 3.1415927;
    double L;
    std::cout << "Введите длину окружности L: ";
    L = get_positive_value();

    double R = L / (2 * kPi);
    double S = kPi * R * R;

    std::cout << "Радиус R: " << R << "\n";
    std::cout << "Площадь S: " << S << "\n";
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