#include <iostream>
#include "russian.h"
int get_natural_value ();

int main() {
    try {
    setRussianLocale();
    int number;
    std::cout << "Введите трехзначное число: ";
    number = get_natural_value();
    if ( number < 1000) {
    int digit1 = number / 100;
    int digit2 = (number / 10) % 10;
    int digit3 = number % 10;

    int reversed = digit3 * 100 + digit2 * 10 + digit1;

    std::cout << "Перевернутое число: " << reversed << "\n";
    } else {
        std::cout << " Ваше число не трёхзначное!";
    }
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