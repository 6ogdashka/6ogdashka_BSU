#include <iostream>
#include "russian.h"
int get_natural_value ();

int main() {
    try {
    setRussianLocale();
    int number;
    std::cout << "Введите трехзначное число: ";
    number = get_natural_value();

    int first_digit = number / 100;
    int remaining = number % 100;
    int result = remaining * 10 + first_digit;

    std::cout << "Результат: " << result << "\n";
    } catch ( const char* msg) { std::cout << msg;}
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