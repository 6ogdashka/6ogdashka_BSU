#include <iostream>

int main() {
    double a;
    std::cout << "Введите сторону квадрата a: ";
    std::cin >> a;

    double perimeter = 4 * a;
    double area = a * a;

    std::cout << "Периметр: " << perimeter << "\n";
    std::cout << "Площадь: " << area << "\n";

    return 0;
}