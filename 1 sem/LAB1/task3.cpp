#include <iostream>
#include "russian.h"
int get_natural_value ();

int main() {
    try {
    setRussianLocale();
    int number;
    std::cout << "Введите трехзначное число: ";
    number = get_natural_value();

    int digit1 = number / 100;
    int digit2 = (number / 10) % 10;
    int digit3 = number % 10;

    int result = digit1 * 100000 + digit1 * 10000 + digit2 * 1000 + digit2 * 100 + digit3 * 10 + digit3;

    std::cout << "Результат: " << result << "\n";
    } catch ( const char* msg) { std::cout <<  msg;}
    return 0;
}

int get_natural_value () {
    int value;
    if (( std::cin >> value ) && ( value >= 1)) {
        return value;
    } else {
        throw " Число должно быть натуральным ";
    }
}