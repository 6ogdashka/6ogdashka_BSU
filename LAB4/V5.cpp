// вы отсортили после того как сделал, поэтому я делал 5 вариант а не 6.
#include <iostream>
#include <iomanip>
#include <limits>
#include <random>
#include <stdexcept>
void input_size_of_matrix(int32_t& rows, int32_t& columns);
void cin_matrix(int**& matrix, int32_t rows, int32_t columns);
void random_generator_choise(int**& matrix, int32_t rows, int32_t columns);
void old_random_generate_matrix(int**& matrix, int32_t rows, int32_t columns);
void new_random_generate_matrix(int**& matrix, int32_t rows, int32_t columns);
void allocate_matrix(int**& mattrix, int32_t rows, int32_t columns);
bool search_negative_number_in_row(int*& row, int32_t size);
int product_of_element_in_row(int*& row, int32_t size);
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
    int32_t rows{};
    int32_t columns{};
    int** matrix{nullptr};
    try {
        input_choise(matrix, rows, columns);
        solve(matrix, rows, columns);
    } catch (const char* msg) {
        std::cout << msg;
    }
    delete_matrix(matrix, rows, columns);
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
    std::cout << " Input rows count: ";
    rows = get_natural_value();
    std::cout << " Input columns count: ";
    columns = get_natural_value();
}

void allocate_matrix(int**& matrix, int32_t rows, int32_t columns) {
    matrix = new int*[rows];
    for (int32_t i{}; i < rows; ++i) {
        matrix[i] = new int[columns];
    }
}

void cin_matrix(int**& matrix, int32_t rows, int32_t columns) {
    for (int i{}; i < rows; ++i) {
        for (int j{}; j < columns; ++j) {
            if (!(std::cin >> matrix[i][j])) {
                throw std::invalid_argument("one elements of matrix entered incorrectly");
            }
        }
    }
}

void old_random_generate_matrix(int**& matrix, int32_t rows, int32_t columns) {
    time_t random_seed{time(NULL)};
    srand(random_seed);
    int32_t left_range_of_elements{};
    int32_t right_range_of_element{};
    std::cout << " Input range of value of element: ";
    if (!((std::cin >> left_range_of_elements) && (std::cin >> right_range_of_element))) {
        throw std::range_error("Incorrectly range");
    }
    if (left_range_of_elements > right_range_of_element) {
        std::swap(left_range_of_elements, right_range_of_element);
    }
    for (int i{}; i < rows; ++i) {
        for (int32_t j{}; j < columns; ++j) {
            matrix[i][j] = rand() % (right_range_of_element - left_range_of_elements + 1) +
                           left_range_of_elements;
            ;
        }
    }
}

void new_random_generate_matrix(int**& matrix, int32_t rows, int32_t columns) {
    std::random_device rd;
    std::mt19937 gen(rd());
    int32_t left_range_of_elements{};
    int32_t right_range_of_element{};
    std::cout << " Input range of value of element: ";
    if (!((std::cin >> left_range_of_elements) && (std::cin >> right_range_of_element))) {
        throw std::range_error(" Incorrectly range");
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

void random_generator_choise(int**& matrix, int32_t rows, int32_t columns) {
    std::string type{};
    std::cout << " Choose random generator: write 'old' if you want old generator"
              << " or write 'new' if you want new generator: ";
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
        throw std::invalid_argument("you chosed incorrect generator");
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

int product_of_element_in_row(int*& row, int32_t size) {
    int product{1};
    for (int32_t i{}; i < size; ++i) {
        product *= row[i];
    }
    return product;
}

void product_of_element_in_positive_rows_in_matrix(int**& matrix, int32_t rows, int32_t columns) {
    int counter{};
    for (int i{}; i < rows; ++i) {
        if (search_negative_number_in_row(matrix[i], columns)) {
            std::cout << "all elements in " << i << " row is positive, product of thit row is: "
                      << product_of_element_in_row(matrix[i], columns) << std::endl;
            ++counter;
        }
    }
    if (counter == 0) {
        std::cout << " all rows have negative element" << std::endl;
    }
}

void swap_rows(int**& matrix, int first_rows, int second_row, int32_t size) {
    for (int i{}; i < size; ++i) {
        std::swap(matrix[first_rows][i], matrix[second_row][i]);
    }
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
    int32_t max{max_element_in_matrix(matrix, rows, columns)};
    int row_index{};
    row_index = search_rows_with_max_element(matrix, rows, columns, max);
    // std::cout << row_index << '\n';
    swap_rows(matrix, 0, row_index, columns);
    if (matrix[0][0] == max_element_in_matrix(matrix, rows, columns)) {
        return;
    }
    int column_index{};
    column_index = search_column_with_max_element(matrix, rows, columns, max);
    // std::cout << column_index << '\n';
    swap_columns(matrix, 0, column_index, rows);
}

void cout_matrix(int**& matrix, int32_t rows, int32_t columns) {
    for (int i{}; i < rows; ++i) {
        for (int j{}; j < columns; ++j) {
            std::cout << std::setw(columns) << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void input_choise(int**& matrix, int32_t& rows, int32_t& columns) {
    std::cout << "Выберите формат ввода элементов матрицы:" << std::endl;
    std::cout << "Введите еденицу(1),если вы ходите ввести матрицу с клавиатуры" << std::endl;
    std::cout
        << "Введите двойку(2), если хотите, чтобы матрица была заполнена произвольными числами"
        << std::endl;
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
            std::cout << "Generated matrix is: " << std::endl;
            cout_matrix(matrix, rows, columns);
            break;
        }
        default: {
            throw std::invalid_argument ("You choose incorrert variant, try again");
        }
    }
}

void handle_input(int**& matrix, int32_t rows, int32_t columns) {
    allocate_matrix(matrix, rows, columns);
    std::cout << " input matrix" << std::endl;
    cin_matrix(matrix, rows, columns);
}

void solve(int32_t**& matrix, int32_t rows, int32_t columns) {
    product_of_element_in_positive_rows_in_matrix(matrix, rows, columns);
    special_matrix_sort(matrix, rows, columns);
    std::cout << "Sorted matrix is: " << std::endl;
    cout_matrix(matrix, rows, columns);
}

void delete_matrix(int**& matrix, int32_t rows, int32_t columns) {
    for (int32_t i = 0; i < rows; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
    matrix = nullptr;
}