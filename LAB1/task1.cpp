#include <iostream>

double get_double_value ();

int main() {
    try {
    double a;
    std::cout << "Введите сторону квадрата a: ";
    a = get_double_value();

    double perimeter = 4 * a;
    double area = a * a;

    std::cout << "Периметр: " << perimeter << "\n";
    std::cout << "Площадь: " << area << "\n";
    } catch ( const char* msg) { std::cout << msg;}
    return 0;
}

double get_double_value () {
    double value;
    if (( std::cin >> value ) && ( value > 0)) {
        return value;
    } else {
        throw " Число должно быть натуральным ";
    }
}