#include <iostream>

int main() {
    const double kPi = 3.1415927;
    double L;
    std::cout << "Введите длину окружности L: ";
    std::cin >> L;

    double R = L / (2 * kPi);
    double S = kPi * R * R;

    std::cout << "Радиус R: " << R << "\n";
    std::cout << "Площадь S: " << S << "\n";

    return 0;
}