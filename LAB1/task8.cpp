#include <iostream>
#include <cmath>

int main() {
    double x1, y1, x2, y2, x3, y3;
    std::cout << "Введите координаты вершин треугольника (x1 y1 x2 y2 x3 y3): ";
    std::cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;

    double a = std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2));
    double b = std::sqrt(std::pow(x3 - x2, 2) + std::pow(y3 - y2, 2));
    double c = std::sqrt(std::pow(x1 - x3, 2) + std::pow(y1 - y3, 2));

    double perimeter = a + b + c;
    double p = perimeter / 2;
    double area = std::sqrt(p * (p - a) * (p - b) * (p - c));

    std::cout << "Периметр: " << perimeter << "\n";
    std::cout << "Площадь: " << area << "\n";

    return 0;
}