#include <iostream>
#include <cmath>
#include "russian.h"

void task10();
int countDigits(int number);
int sumOfPoweredDigits(int number, int power);
bool isArmstrongNumber( int number);

int main() {
    try {
        setRussianLocale();
        std::cout << "Задача 10: Числа Армстронга\n\n";
        task10();
    } catch (const char* msg) { 
        std::cout << msg; 
    }
    return 0;
}

int countDigits(int number) {
    int count = 0;
    while (number > 0) {
        count++;
        number /= 10;
    }
    return count;
}

int sumOfPoweredDigits(int number, int power) {
    int sum = 0;
    while (number > 0) {
        int digit = number % 10;
        sum += std::pow(digit, power);
        number /= 10;
    }
    return sum;
}

bool isArmstrongNumber(int number) {
    int digitCount = countDigits(number);
    int sum = sumOfPoweredDigits(number, digitCount);
    return sum == number;
}

void task10() {
    std::cout << "=== Задача 10: Числа Армстронга ===\n";
    
    int N;
    std::cout << "Введите до какого числа считать числа Армстронга: ";
    std::cin >> N;

    if (N < 1) {
        throw "N должно быть натуральным числом (N >= 1)\n\n";
    }

    std::cout << "Числа Армстронга меньшие " << N << ":\n";
    
    int counter = 0;
    for (int i = 1; i < N; i++) {
        if (isArmstrongNumber(i)) {
            ++counter;
            std::cout << "Число Армстронга №" << counter << ": " << i << "\n";
        }
    }
    
    if (counter == 0) {
        throw "Чисел Армстронга не найдено.\n\n";
    }
}