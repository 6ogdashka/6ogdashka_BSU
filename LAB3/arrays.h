#ifndef ARRAYS_H
#define ARRAYS_H

#include <vector>
#include <array>

const int MAX_SIZE = 1000;

// Объявления функций для каждого типа массива
void solve_vector();
void solve_std_array();
void solve_static_array();
void solve_dynamic_array();

// Общие вспомогательные функции
double get_double_value();
int get_array_size(int &size);

#endif