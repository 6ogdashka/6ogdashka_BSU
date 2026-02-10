// вы отсортили таблицу уже после того как сделал, поэтому я делал 5 вариант а не 6.
// так же я попросил AI сделать оформление более красивым.

#include <iomanip>
#include <iostream>
#include <limits>
#include "russian.h"
#include <random>
#include <stdexcept>

void input_size_of_matrix(int32_t& rows, int32_t& columns);
void cin_matrix(int**& matrix, int32_t rows, int32_t columns);
void random_generator_choise(int**& matrix, int32_t rows, int32_t columns);
void old_random_generate_matrix(int**& matrix, int32_t rows, int32_t columns);
void new_random_generate_matrix(int**& matrix, int32_t rows, int32_t columns);
void allocate_matrix(int**& mattrix, int32_t rows, int32_t columns);
bool search_negative_number_in_row(int*& row, int32_t size);
long long product_of_element_in_row(int*& row, int32_t size);
void product_of_element_in_positive_rows_in_matrix(int**& matrix, int32_t rows, int32_t columns);
int max_element_in_matrix(int**& matrix, int32_t rows, int32_t columns);
int search_rows_with_max_element(int**& matrix, int32_t rows, int32_t columns, int32_t max);
int search_column_with_max_element(int**& matrix, int32_t rows, int32_t columns, int32_t max);
void swap_rows(int**& matrix, int first_rows, int second_row, int32_t size);
void swap_columns(int**& matrix, int first_column, int second_column, int32_t size);
void cout_matrix(int**& matrix, int32_t rows, int32_t columns);
void input_choise(int**& matrix, int32_t& rows, int32_t& columns);
void handle_input(int**& matrix, int32_t rows, int32_t columns);
void random_input(int**& matrix, int32_t rows, int32_t columns);
void solve(int32_t**& matrix, int32_t rows, int32_t columns);
void delete_matrix(int**& matrix, int32_t rows, int32_t columns);

int main() {
    setRussianLocale();
    int32_t rows{};
    int32_t columns{};
    int** matrix{nullptr};
    try {
        input_choise(matrix, rows, columns);
        solve(matrix, rows, columns);
    } catch (const char* msg) {
        std::cout << msg;
    }
    if ( matrix != nullptr) { delete_matrix(matrix, rows, columns); };
    return 0;
}

inline int get_natural_value() {
    int32_t value{};
    if (!((std::cin >> value) && (value >= 1))) {
        throw std::invalid_argument(" value is innaturaly");
    }
    return value;
}

void input_size_of_matrix(int32_t& rows, int32_t& columns) {
    std::cout << "\n╔══════════════════════════════════════════════╗" << std::endl;
    std::cout << "║           ВВОД РАЗМЕРА МАТРИЦЫ              ║" << std::endl;
    std::cout << "╚══════════════════════════════════════════════╝" << std::endl;

    std::cout << "➤ Введите количество строк: ";
    rows = get_natural_value();
    std::cout << "➤ Введите количество столбцов: ";
    columns = get_natural_value();

    std::cout << "✓ Размер матрицы: " << rows << " × " << columns << std::endl;
}

void allocate_matrix(int**& matrix, int32_t rows, int32_t columns) {
    matrix = new int*[rows];
    for (int32_t i{}; i < rows; ++i) {
        matrix[i] = new int[columns];
    }
}

void cin_matrix(int**& matrix, int32_t rows, int32_t columns) {
    for (int i{}; i < rows; ++i) {
        std::cout << "Строка " << i << ": ";
        for (int j{}; j < columns; ++j) {
            if (!(std::cin >> matrix[i][j])) {
                throw std::invalid_argument("Ошибка: элемент введен некорректно");
            }
        }
    }
    std::cout << "✓ Матрица успешно введена" << std::endl;
}

void old_random_generate_matrix(int**& matrix, int32_t rows, int32_t columns) {
    std::cout << "\n─── Классический генератор ───" << std::endl;
    time_t random_seed{time(NULL)};
    srand(random_seed);
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

    std::cout << "✓ Диапазон: [" << left_range_of_elements << ", " << right_range_of_element << "]"
              << std::endl;

    for (int i{}; i < rows; ++i) {
        for (int32_t j{}; j < columns; ++j) {
            matrix[i][j] = rand() % (right_range_of_element - left_range_of_elements + 1) +
                           left_range_of_elements;
        }
    }
}

void new_random_generate_matrix(int**& matrix, int32_t rows, int32_t columns) {
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
        std::cout << "⚠  Диапазон автоматически исправлен" << std::endl;
        std::swap(left_range_of_elements, right_range_of_element);
    }

    std::cout << "✓ Диапазон: [" << left_range_of_elements << ", " << right_range_of_element << "]"
              << std::endl;

    std::uniform_int_distribution<int> distrib(left_range_of_elements, right_range_of_element);
    for (int i{}; i < rows; ++i) {
        for (int j{}; j < columns; ++j) {
            matrix[i][j] = distrib(gen);
        }
    }
}

void random_generator_choise(int**& matrix, int32_t rows, int32_t columns) {
    std::cout << "\n╔══════════════════════════════════════════════╗" << std::endl;
    std::cout << "║     ВЫБОР ГЕНЕРАТОРА СЛУЧАЙНЫХ ЧИСЕЛ       ║" << std::endl;
    std::cout << "╠══════════════════════════════════════════════╣" << std::endl;
    std::cout << "║ • 'old' - классический генератор (rand())   ║" << std::endl;
    std::cout << "║ • 'new' - современный генератор (mt19937)   ║" << std::endl;
    std::cout << "╚══════════════════════════════════════════════╝" << std::endl;
    std::cout << "➤ Ваш выбор: ";

    std::string type{};
    std::cin >> type;
    if (type == "old") {
        allocate_matrix(matrix, rows, columns);
        old_random_generate_matrix(matrix, rows, columns);
        return;
    } else if (type == "new") {
        allocate_matrix(matrix, rows, columns);
        new_random_generate_matrix(matrix, rows, columns);
        return;
    } else {
        throw std::invalid_argument("Ошибка: выбран неверный генератор");
    }
}

bool search_negative_number_in_row(int*& row, int32_t size) {
    for (int32_t i{}; i < size; ++i) {
        if (row[i] < 0) {
            return false;
        }
    }
    return true;
}

long long product_of_element_in_row(int*& row, int32_t size) {
    long long product{1};
    for (int32_t i{}; i < size; ++i) {
        product *= row[i];
    }
    return product;
}

void product_of_element_in_positive_rows_in_matrix(int**& matrix, int32_t rows, int32_t columns) {
    std::cout << "\n─── Произведения в строках без отрицательных элементов ───" << std::endl;
    int counter{};
    for (int i{}; i < rows; ++i) {
        if (search_negative_number_in_row(matrix[i], columns)) {
            std::cout << "✓ Строка " << i << ": все элементы положительные" << std::endl;
            std::cout << "  Произведение: " << product_of_element_in_row(matrix[i], columns)
                      << std::endl;
            ++counter;
        }
    }
    if (counter == 0) {
        std::cout << "✗ Все строки содержат отрицательные элементы" << std::endl;
    }
}

void swap_rows(int**& matrix, int first_rows, int second_row, int32_t size) {
    std::swap(matrix[first_rows],matrix[second_row]);
}

void swap_columns(int**& matrix, int32_t first_column, int32_t second_column, int32_t size) {
    for (int i{}; i < size; ++i) {
        std::swap(matrix[i][first_column], matrix[i][second_column]);
    }
}

int max_element_in_matrix(int**& matrix, int32_t rows, int32_t columns) {
    int max{std::numeric_limits<int>::min()};
    for (int i{}; i < rows; ++i) {
        for (int j{}; j < columns; ++j) {
            if (matrix[i][j] > max) {
                max = matrix[i][j];
            }
        }
    }
    return max;
}

int search_rows_with_max_element(int**& matrix, int32_t rows, int32_t columns, int32_t max) {
    int index{};
    for (int i{}; i < rows; ++i) {
        for (int j{}; j < columns; ++j) {
            if (matrix[i][j] == max) {
                index = i;
                break;
            }
        }
    }
    return index;
}

int search_column_with_max_element(int**& matrix, int32_t rows, int32_t columns, int32_t max) {
    int index{};
    for (int i{}; i < rows; ++i) {
        for (int j{}; j < columns; ++j) {
            if (matrix[i][j] == max) {
                index = j;
                break;
            }
        }
    }
    return index;
}

void special_matrix_sort(int** matrix, int32_t rows, int32_t columns) {
    int32_t max = max_element_in_matrix(matrix, rows, columns);
    int row_index = search_rows_with_max_element(matrix, rows, columns, max);
    if (row_index != 0) {
        swap_rows(matrix, 0, row_index, columns);
    }
    int column_index = 0;
    for (int j = 0; j < columns; ++j) {
        if (matrix[0][j] == max) {
            column_index = j;
            break;
        }
    }
    if (column_index != 0) {
        swap_columns(matrix, 0, column_index, rows);
    }
}

void cout_matrix(int**& matrix, int32_t rows, int32_t columns) {
    for (int i{}; i < rows; ++i) {
        for (int j{}; j < columns; ++j) {
            std::cout << std::setw(6) << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void input_choise(int**& matrix, int32_t& rows, int32_t& columns) {
    std::cout << "╔══════════════════════════════════════════════╗" << std::endl;
    std::cout << "║        ВВОД ЭЛЕМЕНТОВ МАТРИЦЫ               ║" << std::endl;
    std::cout << "╠══════════════════════════════════════════════╣" << std::endl;
    std::cout << "║ 1 - Ввод матрицы с клавиатуры               ║" << std::endl;
    std::cout << "║ 2 - Заполнение случайными числами           ║" << std::endl;
    std::cout << "╚══════════════════════════════════════════════╝" << std::endl;
    std::cout << "➤ Выберите вариант: ";

    int numb{};
    std::cin >> numb;
    switch (numb) {
        case 1: {
            input_size_of_matrix(rows, columns);
            handle_input(matrix, rows, columns);
            break;
        }
        case 2: {
            input_size_of_matrix(rows, columns);
            random_generator_choise(matrix, rows, columns);
            std::cout << "\n╔══════════════════════════════════════════════╗" << std::endl;
            std::cout << "║        СГЕНЕРИРОВАННАЯ МАТРИЦА               ║" << std::endl;
            std::cout << "╚══════════════════════════════════════════════╝" << std::endl;
            cout_matrix(matrix, rows, columns);
            break;
        }
        default: {
            throw std::invalid_argument("Ошибка: выбран неверный вариант!");
        }
    }
}

void handle_input(int**& matrix, int32_t rows, int32_t columns) {
    allocate_matrix(matrix, rows, columns);
    std::cout << "\n╔══════════════════════════════════════════════╗" << std::endl;
    std::cout << "║           РУЧНОЙ ВВОД МАТРИЦЫ               ║" << std::endl;
    std::cout << "╚══════════════════════════════════════════════╝" << std::endl;
    std::cout << "Введите элементы матрицы " << rows << " × " << columns << ":" << std::endl;
    cin_matrix(matrix, rows, columns);
}

void solve(int32_t**& matrix, int32_t rows, int32_t columns) {
    std::cout << "\n╔══════════════════════════════════════════════╗" << std::endl;
    std::cout << "║           РЕЗУЛЬТАТЫ ОБРАБОТКИ              ║" << std::endl;
    std::cout << "╚══════════════════════════════════════════════╝" << std::endl;

    product_of_element_in_positive_rows_in_matrix(matrix, rows, columns);
    special_matrix_sort(matrix, rows, columns);

    std::cout << "\n╔══════════════════════════════════════════════╗" << std::endl;
    std::cout << "║         ОТСОРТИРОВАННАЯ МАТРИЦА             ║" << std::endl;
    std::cout << "╚══════════════════════════════════════════════╝" << std::endl;
    cout_matrix(matrix, rows, columns);
}

void delete_matrix(int**& matrix, int32_t rows, int32_t columns) {
    for (int32_t i = 0; i < rows; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
    matrix = nullptr;
}