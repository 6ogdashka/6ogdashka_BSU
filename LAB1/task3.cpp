#include <iostream>

int main() {
    int number;
    std::cout << "Введите трехзначное число: ";
    std::cin >> number;

    int digit1 = number / 100;
    int digit2 = (number / 10) % 10;
    int digit3 = number % 10;

    int result = digit1 * 100000 + digit1 * 10000 + digit2 * 1000 + digit2 * 100 + digit3 * 10 + digit3;

    std::cout << "Результат: " << result << "\n";

    return 0;
}