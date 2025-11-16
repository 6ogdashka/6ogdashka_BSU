#include <iostream>

int main() {
    int number;
    std::cout << "Введите трехзначное число: ";
    std::cin >> number;

    int digit1 = number / 100;
    int digit2 = (number / 10) % 10;
    int digit3 = number % 10;

    int sum = digit1 + digit2 + digit3;
    int product = digit1 * digit2 * digit3;

    std::cout << "Сумма цифр: " << sum << "\n";
    std::cout << "Произведение цифр: " << product << "\n";

    return 0;
}