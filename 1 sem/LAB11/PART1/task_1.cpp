#include <cstddef>
#include <cstdint>
#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <stdexcept>

void random_generate_matrix(std::vector<std::vector<int>>& matrix, int32_t rows, int32_t columns); 
int32_t max_element_in_matrix(const std::vector<std::vector<int>>& matrix, std::pair<size_t,size_t>& place);
void delete_row_and_column(std::vector<std::vector<int>>& matrix, std::pair<size_t,size_t> place);
void sort_by_sum(std::vector<std::vector<int>>& matrix);

int main () {
    try {
        std::vector<std::vector<int>> mtrx;
        int32_t rows, columns;
        std::cout << "─── Размеры матрицы ───\n";
        std::cout << "Введите размеры матрицы\n";
        std::cout << "Количество строк: ";
        std::cin >> rows;
        std::cout << "Количество столбцов: ";
        std::cin >> columns;
        random_generate_matrix(mtrx, rows, columns);
        std::pair<size_t,size_t> place{};
        int32_t max = max_element_in_matrix(mtrx, place);
        std::cout << "Максимальный элемент: " << max << " на позиции [" 
                  << place.first << "," << place.second << "]\n";
        delete_row_and_column(mtrx, place);
        sort_by_sum(mtrx);
    } catch (const std::exception& e) { 
        std::cout << "Ошибка: " << e.what() << std::endl; 
    }
}

void random_generate_matrix(std::vector<std::vector<int>>& matrix, int32_t rows, int32_t columns) {
    std::cout << "\n─── Современный генератор ───" << std::endl;
    std::random_device rd;
    std::mt19937 gen(rd());
    int32_t left_range_of_elements{};
    int32_t right_range_of_element{};

    std::cout << "➤ Введите диапазон значений элементов:" << std::endl;
    std::cout << "  Минимальное значение: ";
    if (!(std::cin >> left_range_of_elements)) {
        throw std::range_error("Ошибка: некорректное минимальное значение");
    }
    std::cout << "  Максимальное значение: ";
    if (!(std::cin >> right_range_of_element)) {
        throw std::range_error("Ошибка: некорректное максимальное значение");
    }

    if (left_range_of_elements > right_range_of_element) {
        std::swap(left_range_of_elements, right_range_of_element);
    }

    std::uniform_int_distribution<int> distrib(left_range_of_elements, right_range_of_element);
    matrix.resize(rows);
    for (int i = 0; i < rows; ++i) {
        matrix[i].resize(columns); 
        for (int j = 0; j < columns; ++j) {
            matrix[i][j] = distrib(gen);
        }
    }
}

int32_t max_element_in_matrix(const std::vector<std::vector<int>>& matrix, std::pair<size_t,size_t>& place) {
    if (matrix.empty()) throw std::runtime_error("Матрица пуста");
    
    int32_t max = INT32_MIN;
    for (size_t i = 0; i < matrix.size(); ++i) {
        for (size_t j = 0; j < matrix[i].size(); ++j) {
            if (matrix[i][j] > max) {
                max = matrix[i][j];
                place.first = i;
                place.second = j;
            }
        }
    }
    return max;
}

void delete_row_and_column(std::vector<std::vector<int>>& matrix, std::pair<size_t,size_t> place) {
    if (matrix.empty()) return;
    
    if (place.first < matrix.size()) {
        matrix.erase(matrix.begin() + place.first);
    }
    
    for (auto& row : matrix) {
        if (place.second < row.size()) {
            row.erase(row.begin() + place.second);
        }
    }
} 

void sort_by_sum(std::vector<std::vector<int>>& matrix) {
    if (matrix.empty()) return;
    
    std::vector<std::pair<int, size_t>> row_sums; 
    
    for (size_t i = 0; i < matrix.size(); ++i) {
        int sum = 0;
        for (size_t j = 0; j < matrix[i].size(); ++j) {
            sum += matrix[i][j];
        }
        row_sums.push_back({sum, i});
    }

    for (size_t i = 0; i < row_sums.size(); ++i) {
        for (size_t j = 0; j < row_sums.size() - i - 1; ++j) {
            if (row_sums[j].first > row_sums[j + 1].first) {
                std::swap(row_sums[j], row_sums[j + 1]);
            }
        }
    }
    
    std::vector<std::vector<int>> sorted_matrix;
    
    for (size_t i = 0; i < row_sums.size(); ++i) {
        size_t original_row_index = row_sums[i].second;
        sorted_matrix.push_back(matrix[original_row_index]);
    }
    
    matrix = sorted_matrix;
}