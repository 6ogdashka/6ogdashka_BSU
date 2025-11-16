#include <iostream>
#include <cmath>

int main() {
    const double kPi = 3.1415927;
    double S;
    std::cout << "Введите площадь круга S: ";
    std::cin >> S;

    double R = std::sqrt(S / kPi);
    double D = 2 * R;
    double L = 2 * kPi * R;

    std::cout << "Диаметр D: " << D << "\n";
    std::cout << "Длина окружности L: " << L << "\n";

    return 0;
}