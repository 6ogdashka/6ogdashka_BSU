#include "fraction.h"
#include "fraction.cpp"
#include <iostream>
#include <vector>
#include "russian.h"

int main() {
    setRussianLocale();
    std::cout << "=== ДЕМОНСТРАЦИЯ КЛАССА FRACTION ===" << std::endl;
    
    // много удобных конструкторов
    std::cout << "\n1. КОНСТРУКТОРЫ:" << std::endl;
    Fraction def;                           // По умолчанию
    Fraction from_ints(3, 4);               // Задание знаменателя и числителя
    Fraction from_double(0.75);             // Из double
    Fraction copy(from_ints);               // Копирования
    Fraction moved(std::move(copy));        // Перемещения
    
    std::cout << "По умолчанию: " << def << std::endl;
    std::cout << "Из целых (3,4): " << from_ints << std::endl;
    std::cout << "Из double (0.75): " << from_double << std::endl;
    std::cout << "Копия: " << moved << std::endl;
    std::cout << "После перемещения: " << copy << std::endl;

    // реализованые все бaзoвые операции
    std::cout << "\n2. БАЗОВЫЕ ОПЕРАЦИИ:" << std::endl;
    Fraction a(2, 3), b(1, 4);
    std::cout << a << " + " << b << " = " << a + b << std::endl;
    std::cout << a << " * " << b << " = " << a * b << std::endl;
    std::cout << "Обратная к " << a << ": " << !a << std::endl;

    // все вычесления довольно точные
    std::cout << "\n3. ТОЧНОСТЬ ДРОБЕЙ:" << std::endl;
    Fraction exact = Fraction(1, 3) * 3;
    double approx = 1.0/3.0 * 3.0;
    std::cout << "1/3 * 3 = " << exact << " (точно!)" << std::endl;
    std::cout << "1.0/3.0 * 3.0 = " << approx << " (приближенно)" << std::endl;

    // мат методы
    std::cout << "\n4. НОВЫЕ МАТЕМАТИЧЕСКИЕ МЕТОДЫ:" << std::endl;
    
    // возведение в степень
    Fraction base(2, 3);
    std::cout << "(" << base << ")^2 = " << base.pow(2) << std::endl;
    std::cout << "(" << base << ")^3 = " << base.pow(3) << std::endl;
    std::cout << "(" << base << ")^(-1) = " << base.pow(-1) << std::endl;
    
    // модуль дроби
    Fraction negative(-3, 4);
    std::cout << "|" << negative << "| = " << abs(negative) << std::endl;
    
    // округление и целая часть
    Fraction f1(7, 2), f2(8, 3), f3(-5, 2);
    std::cout << f1 << " округление: " << f1.round() << ", целая часть: " << f1.floor() <<  std::endl;
    std::cout << f2 << " округление: " << f2.round() << ", целая часть: " << f2.floor() << std::endl;
    std::cout << f3 << " округление: " << f3.round() << ", целая часть: " << f3.floor() << std::endl;
    
    // дробная часть
    std::cout << f1 << " дробная часть: " << f1.fractional() << std::endl;
    std::cout << f2 << " дробная часть: " << f2.fractional() << std::endl;
    std::cout << "Смешанное представление " << f1 << ": " << f1.floor() << ", " << f1.fractional() << "; " << "Сумма частей равна: " << (f1.floor() + f1.fractional()) << " == " << "f1(" << f1 << ")" << std::endl;

    // считать последовательности
    std::cout << "\n5. РЕКУРРЕНТНАЯ ПОСЛЕДОВАТЕЛЬНОСТЬ:" << std::endl;
    std::cout << "a₁ = 1/2, a₂ = 1/3, aₙ = (aₙ₋₁ + aₙ₋₂) / 2" << std::endl;
    
    std::vector<Fraction> seq = {Fraction(1, 2), Fraction(1, 3)};
    for (int i = 2; i < 6; ++i) {
        Fraction next = (seq[i-1] + seq[i-2]) / Fraction(2);
        seq.push_back(next);
        std::cout << "a" << i+1 << " = " << next << " ≈ " << ToDouble(next) << std::endl;
    }

    // решение задачи на дроби
    std::cout << "\n6. ЗАДАЧА НА СОВМЕСТНУЮ РАБОТУ:" << std::endl;
    std::cout << "Первая бригада выполняет работу за 6 дней, вторая - за 4 дня." << std::endl;
    std::cout << "За сколько дней выполнят работу обе бригады вместе?" << std::endl;
    
    Fraction productivity1(1, 6);  // производительность первой бригады
    Fraction productivity2(1, 4);  // производительность второй бригады
    Fraction total_productivity = productivity1 + productivity2;
    Fraction time_together = Fraction(1) / total_productivity;  // время = работа / производительность
    
    std::cout << "Совместная производительность = 1/6 + 1/4 = " << total_productivity << " работы/день" << std::endl;
    std::cout << "Время выполнения: " << time_together << " дней" << std::endl;
    std::cout << "Или: " << ToDouble(time_together) << " дней" << std::endl;

    return 0;
}