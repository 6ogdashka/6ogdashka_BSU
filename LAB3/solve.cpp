#include <iostream>
#include "arrays.h"
int main() {
    std::cout << "=== Программа работы с массивами ===\n";
    std::cout << "Выберите тип массива:\n";
    std::cout << "1 - std::vector<double> (динамический вектор)\n";
    std::cout << "2 - std::array<double, " << MAX_SIZE << "> (статический массив STL)\n";
    std::cout << "3 - double[" << MAX_SIZE << "] (статический массив C-style)\n";
    std::cout << "4 - double* (динамический массив C-style)\n";
    std::cout << "Ваш выбор: ";
    
    int choice;
    std::cin >> choice;
    
    try {
        switch(choice) {
            case 1: 
                std::cout << "\n--- Работа с std::vector ---\n";
                solve_vector(); 
                break;
            case 2: 
                std::cout << "\n--- Работа с std::array ---\n";
                solve_std_array(); 
                break;
            case 3: 
                std::cout << "\n--- Работа со статическим массивом ---\n";
                solve_static_array(); 
                break;
            case 4: 
                std::cout << "\n--- Работа с динамическим массивом ---\n";
                solve_dynamic_array(); 
                break;
            default: 
                throw "Неверный выбор! Введите число от 1 до 4.";
        }
    } catch (const char* msg) {
        std::cout << "Ошибка: " << msg << std::endl;
        return 1;
    } catch (const std::exception& e) {
        std::cout << "Стандартная ошибка: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}