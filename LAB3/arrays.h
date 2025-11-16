#ifndef ARRAYS_H
#define ARRAYS_H

#include <stdexcept>
#include <vector>
#include <array>
#include <iostream>
#include "static.array.h"

const int MAX_SIZE = 1000;

// Объявления функций для каждого типа массива
void solve_vector();
void solve_std_array();
void solve_static_array();
void solve_dynamic_array();

// Общие вспомогательные функци
inline double get_double_value() {
    double value{};
    if (!(std::cin >> value)) {
        throw std::invalid_argument(" incorrect value ");
    }
    return value;
}
#endif