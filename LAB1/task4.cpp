#include <iostream>

int get_natural_value ();

int main() {
    try {
    int number;
    std::cout << "Введите трехзначное число: ";
    number = get_natural_value();
    if ( number < 1000) {
    int digit1 = number / 100;
    int digit2 = (number / 10) % 10;
    int digit3 = number % 10;

    int sum = digit1 + digit2 + digit3;
    int product = digit1 * digit2 * digit3;

    std::cout << "Сумма цифр: " << sum << "\n";
    std::cout << "Произведение цифр: " << product << "\n";
    } else {
        std::cout << " Ваше числа не трехзначное! ";
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