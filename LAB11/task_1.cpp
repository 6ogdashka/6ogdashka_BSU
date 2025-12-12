#include <cstddef>
#include <cstdint>
#include <iostream>
#include <random>
#include <vector>

void random_generate_matrix(std::vector<std::vector<int>>& matrix, int32_t rows, int32_t columns); 
int32_t max_element_in_matrix(std::vector<std::vector<int>>& matrix, int32_t rows, int32_t columns, std::pair<size_t,size_t>& place);
void delete_row_and_column( std::vector<std::vector<int>>& matrix, std::pair<size_t,size_t> place);

int main () {
    try {
        std::vector<std::vector<int>> vec{};
        int32_t rows, columns;
        std::cout << "─── Размеры матрицы ───\n";
        std::cout << "Введите размеры матрицы\n";
        std::cout << "Количество строк: ";
        std::cin >> rows;
        std::cout << "Количество столбцов: ";
        std::cin >> columns;
        random_generate_matrix(vec, rows, columns);
        std::pair<size_t,size_t> place{};
        int32_t max = max_element_in_matrix(vec, rows,columns, place);
        delete_row_and_column(vec, place);

    } catch ( const char* msg) { std::cout <<msg; }
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
    for (int i{}; i < rows; ++i) {
        for (int j{}; j < columns; ++j) {
            matrix[i][j] = distrib(gen);
        }
    }
}

int32_t max_element_in_matrix(std::vector<std::vector<int>>& matrix, int32_t rows, int32_t columns, std::pair<size_t,size_t>& place) {
    int32_t max{INT32_MIN};
    for (size_t i{}; i < rows; ++i) {
        for (size_t j{}; j < columns; ++j) {
            if (matrix[i][j] > max) {
                max = matrix[i][j];
                place.first = i;
                place.second = j;
            }
        }
    }
    return max;
}

void delete_row_and_column( std::vector<std::vector<int>>& matrix, std::pair<size_t,size_t> place) {
    matrix.erase(matrix.begin() + place.first);
    for ( std::vector<int> i : matrix ) {
        i.erase(i.begin()+place.second);
    }
} 

void sort_by_sum ( std::vector<std::vector<int>> matrix) {

}