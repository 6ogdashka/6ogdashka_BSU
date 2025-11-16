#include <iostream>

int main() {
    int number;
    std::cout << "Введите трехзначное число: ";
    std::cin >> number;

    int digit1 = number / 100;
    int digit2 = (number / 10) % 10;
    int digit3 = number % 10;

    int reversed = digit3 * 100 + digit2 * 10 + digit1;

    std::cout << "Перевернутое число: " << reversed << "\n";

    return 0;
}