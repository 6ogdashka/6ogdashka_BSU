#include <iostream>

int main() {
    int number;
    std::cout << "Введите трехзначное число: ";
    std::cin >> number;

    int first_digit = number / 100;
    int remaining = number % 100;
    int result = remaining * 10 + first_digit;

    std::cout << "Результат: " << result << "\n";

    return 0;
}