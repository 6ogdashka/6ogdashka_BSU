#include "fraction.h"
#include <cmath>
#include <iostream>
#include <vector>
#include "russian.h"

void solve();

int main() {
    setRussianLocale();
    std::cout << "=== ДЕМОНСТРАЦИЯ КЛАССА FRACTION ===" << std::endl;
    
    // ... (предыдущий код main остается без изменений) ...
    
    // много удобных конструкторов
    std::cout << "\n1. КОНСТРУКТОРЫ:" << std::endl;
    Fraction def;                           // По умолчанию
    Fraction from_ints(3, 4, true);         // Задание знаменателя и числителя с сокращением
    Fraction from_double(0.75);             // Из double
    Fraction copy(from_ints);               // Копирования
    Fraction moved(std::move(copy));        // Перемещения
    
    std::cout << "По умолчанию: " << def << std::endl;
    std::cout << "Из целых (3,4) с сокращением: " << from_ints << std::endl;
    std::cout << "Из double (0.75): " << from_double << std::endl;
    std::cout << "Копия: " << moved << std::endl;
    std::cout << "После перемещения: " << copy << std::endl;

    // ДЕМОНСТРАЦИЯ НОВОЙ ОСОБЕННОСТИ - СОКРАЩЕНИЕ ДРОБЕЙ
    std::cout << "\n2. РЕЖИМЫ СОКРАЩЕНИЯ ДРОБЕЙ:" << std::endl;
    
    // Дроби с автоматическим сокращением
    Fraction simplified1(4, 8, true);      // 4/8 автоматически сократится до 1/2
    Fraction simplified2(6, 9, true);      // 6/9 автоматически сократится до 2/3
    
    // Дроби без автоматического сокращения
    Fraction not_simplified1(4, 8, false); // 4/8 останется как есть
    Fraction not_simplified2(6, 9, false); // 6/9 останется как есть
    
    std::cout << "С автоматическим сокращением:" << std::endl;
    std::cout << "4/8 = " << simplified1 << std::endl;
    std::cout << "6/9 = " << simplified2 << std::endl;
    
    std::cout << "Без автоматического сокращения:" << std::endl;
    std::cout << "4/8 = " << not_simplified1 << std::endl;
    std::cout << "6/9 = " << not_simplified2 << std::endl;

    // Покажем, что операции сохраняют режим сокращения
    std::cout << "\n3. ОПЕРАЦИИ С РАЗНЫМИ РЕЖИМАМИ:" << std::endl;
    
    Fraction a(2, 4, false); // без сокращения
    Fraction b(1, 3, true);  // с сокращением
    
    std::cout << "a (без сокращения): " << a << std::endl;
    std::cout << "b (с сокращением): " << b << std::endl;
    std::cout << "a + b = " << (a + b) << " (результат всегда сокращается)" << std::endl;
    std::cout << "a * b = " << (a * b) << " (результат всегда сокращается)" << std::endl;

    // Изменение числителя и знаменателя
    std::cout << "\n4. ИЗМЕНЕНИЕ ЧИСЛИТЕЛЯ И ЗНАМЕНАТЕЛЯ:" << std::endl;
    
    Fraction changeable(8, 12, false); // создаем без сокращения
    std::cout << "Исходная дробь: " << changeable << std::endl;
    
    changeable.SetNum(10); // меняем числитель
    std::cout << "После SetNum(10): " << changeable << " (не сокращена)" << std::endl;
    
    changeable.SetDen(15); // меняем знаменатель
    std::cout << "После SetDen(15): " << changeable << " (не сокращена)" << std::endl;
    
    // Сравним с дробью в режиме сокращения
    Fraction auto_simplified(8, 12, true);
    std::cout << "То же с автосокращением: " << auto_simplified << std::endl;

    // все вычесления довольно точные
    std::cout << "\n5. ТОЧНОСТЬ ДРОБЕЙ:" << std::endl;
    Fraction exact = Fraction(1, 3) * 3;
    double approx = 1.0/3.0 * 3.0;
    std::cout << "1/3 * 3 = " << exact << " (точно!)" << std::endl;
    std::cout << "1.0/3.0 * 3.0 = " << approx << " (приближенно)" << std::endl;

    // мат методы
    std::cout << "\n6. МАТЕМАТИЧЕСКИЕ МЕТОДЫ:" << std::endl;
    
    // возведение в степень
    Fraction base(2, 3);
    std::cout << "(" << base << ")^2 = " << base.pow(2) << std::endl;
    std::cout << "(" << base << ")^3 = " << base.pow(3) << std::endl;
    
    // модуль дроби
    Fraction negative(-3, 4);
    std::cout << "|" << negative << "| = " << abs(negative) << std::endl;
    
    // округление и целая часть
    Fraction f1(7, 2), f2(8, 3), f3(-5, 2);
    std::cout << f1 << " округление: " << f1.round() << ", целая часть: " << f1.floor() <<  std::endl;
    std::cout << f2 << " округление: " << f2.round() << ", целая часть: " << f2.floor() << std::endl;
    
    // дробная часть
    std::cout << f1 << " дробная часть: " << f1.fractional() << std::endl;
    std::cout << f2 << " дробная часть: " << f2.fractional() << std::endl;

    // считать последовательности
    std::cout << "\n7. РЕКУРРЕНТНАЯ ПОСЛЕДОВАТЕЛЬНОСТЬ:" << std::endl;
    std::cout << "a₁ = 1/2, a₂ = 1/3, aₙ = (aₙ₋₁ + aₙ₋₂) / 2" << std::endl;
    
    std::vector<Fraction> seq = {Fraction(1, 2), Fraction(1, 3)};
    for (int i = 2; i < 6; ++i) {
        Fraction next = (seq[i-1] + seq[i-2]) / Fraction(2);
        seq.push_back(next);
        std::cout << "a" << i+1 << " = " << next << " ≈ " << ToDouble(next) << std::endl;
    }

    // решение задачи на дроби
    std::cout << "\n8. ЗАДАЧА НА СОВМЕСТНУЮ РАБОТУ:" << std::endl;
    std::cout << "Первая бригада выполняет работу за 6 дней, вторая - за 4 дня." << std::endl;
    std::cout << "За сколько дней выполнят работу обе бригады вместе?" << std::endl;
    
    Fraction productivity1(1, 6);  // производительность первой бригады
    Fraction productivity2(1, 4);  // производительность второй бригады
    Fraction total_productivity = productivity1 + productivity2;
    Fraction time_together = Fraction(1) / total_productivity;  // время = работа / производительность
    
    std::cout << "Совместная производительность = 1/6 + 1/4 = " << total_productivity << " работы/день" << std::endl;
    std::cout << "Время выполнения: " << time_together << " дней" << std::endl;
    std::cout << "Или: " << ToDouble(time_together) << " дней" << std::endl;

    // задача через дроби
    solve();

    return 0;
}

// Функция для решения системы линейных уравнений методом Гаусса с дробями
void solve_system_of_equations() {
    std::cout << "\n🎯 РЕШЕНИЕ СИСТЕМЫ ЛИНЕЙНЫХ УРАВНЕНИЙ МЕТОДОМ ГАУССА" << std::endl;
    std::cout << "=====================================================" << std::endl;
    
    // Система уравнений:
    // (1/2)x + (1/3)y + (1/4)z = 1
    // (2/3)x + (1/2)y + (1/5)z = 2  
    // (1/4)x + (2/5)y + (1/3)z = 3
    
    std::cout << "Система уравнений:" << std::endl;
    std::cout << "(1/2)x + (1/3)y + (1/4)z = 1" << std::endl;
    std::cout << "(2/3)x + (1/2)y + (1/5)z = 2" << std::endl;
    std::cout << "(1/4)x + (2/5)y + (1/3)z = 3" << std::endl;
    std::cout << std::endl;
    
    // Матрица коэффициентов 3x3 и вектор правой части
    std::vector<std::vector<Fraction>> matrix = {
        {Fraction(1, 2), Fraction(1, 3), Fraction(1, 4)},
        {Fraction(2, 3), Fraction(1, 2), Fraction(1, 5)},
        {Fraction(1, 4), Fraction(2, 5), Fraction(1, 3)}
    };
    
    std::vector<Fraction> rhs = {Fraction(1), Fraction(2), Fraction(3)};
    
    // Прямой ход метода Гаусса
    int n = matrix.size();
    for (int i = 0; i < n; ++i) {
        // Нормализация текущей строки
        Fraction pivot = matrix[i][i];
        for (int j = i; j < n; ++j) {
            matrix[i][j] = matrix[i][j] / pivot;
        }
        rhs[i] = rhs[i] / pivot;
        
        // Исключение переменной из нижележащих строк
        for (int k = i + 1; k < n; ++k) {
            Fraction factor = matrix[k][i];
            for (int j = i; j < n; ++j) {
                matrix[k][j] = matrix[k][j] - factor * matrix[i][j];
            }
            rhs[k] = rhs[k] - factor * rhs[i];
        }
    }
    
    // Обратный ход метода Гаусса
    std::vector<Fraction> solution(n);
    for (int i = n - 1; i >= 0; --i) {
        solution[i] = rhs[i];
        for (int j = i + 1; j < n; ++j) {
            solution[i] = solution[i] - matrix[i][j] * solution[j];
        }
    }
    
    // Вывод решения
    std::cout << "Решение системы:" << std::endl;
    std::cout << "x = " << solution[0] << " ≈ " << ToDouble(solution[0]) << std::endl;
    std::cout << "y = " << solution[1] << " ≈ " << ToDouble(solution[1]) << std::endl;
    std::cout << "z = " << solution[2] << " ≈ " << ToDouble(solution[2]) << std::endl;
    std::cout << std::endl;
    
    // Проверка решения
    std::cout << "Проверка решения:" << std::endl;
    Fraction check1 = matrix[0][0] * solution[0] + matrix[0][1] * solution[1] + matrix[0][2] * solution[2];
    Fraction check2 = matrix[1][0] * solution[0] + matrix[1][1] * solution[1] + matrix[1][2] * solution[2];
    Fraction check3 = matrix[2][0] * solution[0] + matrix[2][1] * solution[1] + matrix[2][2] * solution[2];
    
    std::cout << "Уравнение 1: " << check1 << " = " << rhs[0] << " (" << (check1 == rhs[0] ? "✓" : "✗") << ")" << std::endl;
    std::cout << "Уравнение 2: " << check2 << " = " << rhs[1] << " (" << (check2 == rhs[1] ? "✓" : "✗") << ")" << std::endl;
    std::cout << "Уравнение 3: " << check3 << " = " << rhs[2] << " (" << (check3 == rhs[2] ? "✓" : "✗") << ")" << std::endl;
}

// Функция для вычисления определителя матрицы 3x3 с дробями
Fraction determinant_3x3(const std::vector<std::vector<Fraction>>& matrix) {
    return matrix[0][0] * (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1]) -
           matrix[0][1] * (matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0]) +
           matrix[0][2] * (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]);
}

// Функция для решения системы уравнений методом Крамера
void solve_by_cramer() {
    std::cout << "\n🎯 РЕШЕНИЕ СИСТЕМЫ УРАВНЕНИЙ МЕТОДОМ КРАМЕРА" << std::endl;
    std::cout << "============================================" << std::endl;
    
    // Система уравнений:
    // (2/3)x + (1/4)y = 5/6
    // (1/2)x + (3/5)y = 7/8
    
    std::cout << "Система уравнений:" << std::endl;
    std::cout << "(2/3)x + (1/4)y = 5/6" << std::endl;
    std::cout << "(1/2)x + (3/5)y = 7/8" << std::endl;
    std::cout << std::endl;
    
    // Матрица коэффициентов и вектор правой части
    std::vector<std::vector<Fraction>> A = {
        {Fraction(2, 3), Fraction(1, 4)},
        {Fraction(1, 2), Fraction(3, 5)}
    };
    
    std::vector<Fraction> B = {Fraction(5, 6), Fraction(7, 8)};
    
    // Вычисление определителя основной матрицы
    Fraction det_A = A[0][0] * A[1][1] - A[0][1] * A[1][0];
    
    // Матрицы для определителей по методу Крамера
    std::vector<std::vector<Fraction>> A_x = { {B[0], A[0][1]}, {B[1], A[1][1]} };
    std::vector<std::vector<Fraction>> A_y = { {A[0][0], B[0]}, {A[1][0], B[1]} };
    
    Fraction det_A_x = A_x[0][0] * A_x[1][1] - A_x[0][1] * A_x[1][0];
    Fraction det_A_y = A_y[0][0] * A_y[1][1] - A_y[0][1] * A_y[1][0];
    
    // Решение
    Fraction x = det_A_x / det_A;
    Fraction y = det_A_y / det_A;
    
    std::cout << "Определитель основной матрицы: " << det_A << std::endl;
    std::cout << "Определитель для x: " << det_A_x << std::endl;
    std::cout << "Определитель для y: " << det_A_y << std::endl;
    std::cout << std::endl;
    std::cout << "Решение:" << std::endl;
    std::cout << "x = " << x << " ≈ " << ToDouble(x) << std::endl;
    std::cout << "y = " << y << " ≈ " << ToDouble(y) << std::endl;
    std::cout << std::endl;
    
    // Проверка
    Fraction check1 = A[0][0] * x + A[0][1] * y;
    Fraction check2 = A[1][0] * x + A[1][1] * y;
    
    std::cout << "Проверка:" << std::endl;
    std::cout << "Уравнение 1: " << check1 << " = " << B[0] << " (" << (check1 == B[0] ? "✓" : "✗") << ")" << std::endl;
    std::cout << "Уравнение 2: " << check2 << " = " << B[1] << " (" << (check2 == B[1] ? "✓" : "✗") << ")" << std::endl;
}

// Главная функция solve, которая демонстрирует решение сложных задач
void solve() {
    std::cout << "\n" << std::string(60, '=') << std::endl;
    std::cout << "🚀 РЕШЕНИЕ СЛОЖНЫХ МАТЕМАТИЧЕСКИХ ЗАДАЧ С FRACTION" << std::endl;
    std::cout << std::string(60, '=') << std::endl;
    
    solve_by_cramer();
    solve_system_of_equations();
    
    // Дополнительная задача: вычисление сложного выражения
    std::cout << "\n🎯 ВЫЧИСЛЕНИЕ СЛОЖНОГО МАТЕМАТИЧЕСКОГО ВЫРАЖЕНИЯ" << std::endl;
    std::cout << "==============================================" << std::endl;
    
    // Вычисление: ((1/2 + 1/3) * (2/5 - 1/7)) / ((3/4)^2 + 1/6)
    std::cout << "Выражение: ((1/2 + 1/3) × (2/5 - 1/7)) ÷ ((3/4)² + 1/6)" << std::endl;
    
    Fraction part1 = Fraction(1, 2) + Fraction(1, 3);
    Fraction part2 = Fraction(2, 5) - Fraction(1, 7);
    Fraction numerator = part1 * part2;
    
    Fraction part3 = Fraction(3, 4).pow(2);
    Fraction denominator = part3 + Fraction(1, 6);
    
    Fraction result = numerator / denominator;
    
    std::cout << "Числитель: (" << part1 << ") × (" << part2 << ") = " << numerator << std::endl;
    std::cout << "Знаменатель: (" << part3 << ") + (1/6) = " << denominator << std::endl;
    std::cout << "Результат: " << result << " ≈ " << ToDouble(result) << std::endl;
    
    // Проверка точности по сравнению с double
    double double_result = ((1.0/2 + 1.0/3) * (2.0/5 - 1.0/7)) / (std::pow(3.0/4, 2) + 1.0/6);
    std::cout << "Результат double: " << double_result << std::endl;
    std::cout << "Разница: " << std::abs(ToDouble(result) - double_result) << std::endl;
}