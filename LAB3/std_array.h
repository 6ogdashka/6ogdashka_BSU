#pragma once

#include <iostream>
#include <limits>
#include <cstdint>
#include <ctime>
#include <stdexcept>
#include <array>

void input_std_array(std::array<double, MAX_SIZE> &array, int32_t size);
void output_std_array(std::array<double, MAX_SIZE> array, int32_t begin, int32_t end);
int get_std_array_size(int32_t &size);
double get_double_value_std();
void generate_random_std_array(std::array<double, MAX_SIZE> &array, int32_t SIZE, double left_range, double right_range);
double sum_between_indices_std(int32_t begin, int32_t end, std::array<double, MAX_SIZE> array);
int find_max_index_std(std::array<double, MAX_SIZE> array, int32_t size);
int find_min_index_std(std::array<double, MAX_SIZE> array, int32_t size);
bool is_std_array_palindrome(int32_t begin, int32_t end, std::array<double, MAX_SIZE> array);
void find_longest_palindrome_std(int32_t size, std::array<double, MAX_SIZE> array, int32_t &begin_index, int32_t &end_index);
void quick_sort_std_array(int32_t begin_index, int32_t end_index, std::array<double, MAX_SIZE> &array);
void choose_input_method_std(std::array<double, MAX_SIZE> &array, int32_t &size);
void handle_manual_input_std(std::array<double, MAX_SIZE> &array, int32_t size);
void handle_random_input_std(std::array<double, MAX_SIZE> &array, int32_t size);
void process_std_array(std::array<double, MAX_SIZE> &array, int32_t size);

inline void solve_std_array() {
    setRussianLocale();
    
    std::cout << "==============================================================\n";
    std::cout << "|           РАБОТА С МАССИВОМ STD::ARRAY                    |\n";
    std::cout << "==============================================================\n\n";
    
    int32_t size{};
    std::array<double, MAX_SIZE> array{}; 
    try {
        choose_input_method_std(array, size);
        process_std_array(array, size);
    } catch (const char* msg) {
        std::cout << "ОШИБКА: " << msg << std::endl;
    } catch (const std::exception& e) {
        std::cout << "ОШИБКА: " << e.what() << std::endl;
    }
    
    std::cout << "\n==============================================================\n";
    std::cout << "|           ОБРАБОТКА МАССИВА ЗАВЕРШЕНА                   |\n";
    std::cout << "==============================================================\n";
    return;
}

inline int find_min_index_std(std::array<double, MAX_SIZE> array, int32_t size) {
    double min_value{std::numeric_limits<double>::max()};
    int index{};
    for (int i{}; i < size; ++i) {
        if (array[i] < min_value) {
            index = i;
            min_value = array[i];
        }
    }
    return index;
}

inline int find_max_index_std(std::array<double, MAX_SIZE> array, int32_t size) {
    double max_value{std::numeric_limits<double>::min()};
    int index{};
    for (int i{}; i < size; ++i) {
        if (array[i] > max_value) {
            index = i;
            max_value = array[i];
        }
    }
    return index;
}

inline double sum_between_indices_std(int32_t begin, int32_t end, std::array<double, MAX_SIZE> array) {
    double sum{};
    if (begin > end) {
        std::swap(begin, end);
    }
    for (int32_t i{begin}; i <= end; ++i) {
        sum += array[i];
    }
    return sum;
}

inline bool is_std_array_palindrome(int32_t begin, int32_t end, std::array<double, MAX_SIZE> array) {
    for (int32_t i{0}; i <= ((end - begin) / 2); ++i) {
        if (array[begin + i] != array[end - i]) {
            return false;
        }
    }
    return true;
}

inline void find_longest_palindrome_std(int32_t size, std::array<double, MAX_SIZE> array, int32_t &begin_index, int32_t &end_index) {
    begin_index = 0;
    end_index = 0;
    
    for (int32_t i{size - 1}; i >= 1; --i) {
        for (int32_t j{}; j <= (size - i); ++j) {
            if (is_std_array_palindrome(j, j + i, array)) {
                begin_index = j;
                end_index = j + i;
                return;
            }
        }
    }
}

inline void quick_sort_std_array(int32_t begin_index, int32_t end_index, std::array<double, MAX_SIZE> &array) {
    int32_t current_index = static_cast<int>((end_index - begin_index) / 2) + begin_index;
    double current_value{array[current_index]};
    if (end_index - begin_index < 1) {
        return;
    }
    for (int32_t i{begin_index}; i <= end_index; ++i) {
        if ((array[i] <= current_value) && (i > current_index)) {
            double temp{array[current_index + 1]};
            array[current_index + 1] = array[i];
            array[i] = temp;
            array[current_index] = array[current_index + 1];
            array[current_index + 1] = current_value;
            ++current_index; 
        }
        if ((array[i] > current_value) && (i < current_index)) {
            array[current_index] = array[i];
            array[i] = current_value;
            current_index = i;
        }
    }
    if (current_index >= 1) {
        quick_sort_std_array(begin_index, current_index - 1, array);
    }
    if (current_index <= end_index - 1) {
        quick_sort_std_array(current_index + 1, end_index, array);
    }
}

inline void input_std_array(std::array<double, MAX_SIZE> &array, int32_t size) {
    std::cout << ">>> Введите " << size << " элементов массива:" << std::endl;
    for (int i{}; i < size; ++i) {
        std::cout << "Элемент [" << i << "]: ";
        if (!(std::cin >> array[i])) {
            throw std::invalid_argument("некорректное значение элемента");
        }
    }
}

inline void handle_manual_input_std(std::array<double, MAX_SIZE> &array, int32_t size) {
    std::cout << "==============================================================\n";
    std::cout << "|                  РУЧНОЙ ВВОД МАССИВА                     |\n";
    std::cout << "==============================================================\n";
    input_std_array(array, size);
    std::cout << ">>> Массив успешно введен!\n";
}

inline int get_std_array_size(int32_t &size) {
    std::cout << ">>> Введите размер массива (максимум " << MAX_SIZE << "): ";
    if (!(std::cin >> size)) {
        throw std::invalid_argument("некорректный размер");
    }
    if (size <= 0 || size > MAX_SIZE) {
        throw std::invalid_argument("размер должен быть от 1 до " + std::to_string(MAX_SIZE));
    }
    return size;
}

inline void output_std_array(std::array<double, MAX_SIZE> array, int32_t begin, int32_t end) {
    std::cout << "[ ";
    for (int i{begin}; i <= end; ++i) {
        std::cout << array[i];
        if (i < end) std::cout << ", ";
    }
    std::cout << " ]" << std::endl;
}

inline double get_double_value_std() {
    double value{};
    if (!(std::cin >> value)) {
        throw std::invalid_argument("некорректное числовое значение");
    }
    return value;
}

inline void generate_random_std_array(std::array<double, MAX_SIZE> &array, int32_t SIZE, double left_range, double right_range) {
    time_t random_seed{time(NULL)};
    srand(random_seed);
    if (left_range > right_range) {
        std::swap(left_range, right_range);
    }
    for (int i{}; i < SIZE; ++i) {
        double range = right_range - left_range;
        array[i] = left_range + (static_cast<double>(rand()) / RAND_MAX) * range;
    }
}

inline void handle_random_input_std(std::array<double, MAX_SIZE> &array, int32_t size) {
    std::cout << "==============================================================\n";
    std::cout << "|               ГЕНЕРАЦИЯ СЛУЧАЙНОГО МАССИВА               |\n";
    std::cout << "==============================================================\n";
    
    std::cout << ">>> Введите левую границу диапазона: ";
    double left_range{get_double_value_std()};
    std::cout << ">>> Введите правую границу диапазона: ";
    double right_range{get_double_value_std()};
    
    generate_random_std_array(array, size, left_range, right_range);
    std::cout << ">>> Сгенерированный массив: ";
    output_std_array(array, 0, size - 1);
}

inline void choose_input_method_std(std::array<double, MAX_SIZE> &array, int32_t &size) {
    size = get_std_array_size(size);
    
    std::cout << "==============================================================\n";
    std::cout << "|                   ВЫБЕРИТЕ ФОРМАТ ВВОДА                  |\n";
    std::cout << "==============================================================\n";
    std::cout << "  1 - Ввод массива с клавиатуры\n";
    std::cout << "  2 - Заполнение массива случайными числами\n";
    std::cout << "==============================================================\n";
    std::cout << ">>> Ваш выбор: ";
    
    int32_t choice{};
    std::cin >> choice;
    switch (choice) {
        case 1: {
            handle_manual_input_std(array, size);
            break;
        }
        case 2: {
            handle_random_input_std(array, size);
            break;
        }
        default: {
            throw "неверный формат ввода. Пожалуйста, выберите 1 или 2";
        }
    }
}

inline void process_std_array(std::array<double, MAX_SIZE> &array, int32_t size) {
    std::cout << "\n==============================================================\n";
    std::cout << "|                    РЕЗУЛЬТАТЫ ОБРАБОТКИ                  |\n";
    std::cout << "==============================================================\n";
    
    int32_t min_index{find_min_index_std(array, size)};
    int32_t max_index{find_max_index_std(array, size)};
    int32_t begin_index{};
    int32_t end_index{};
    
    std::cout << ">>> Индекс минимального элемента: " << min_index << std::endl;
    std::cout << ">>> Индекс максимального элемента: " << max_index << std::endl;
    std::cout << ">>> Сумма элементов между минимальным и максимальным: " 
              << sum_between_indices_std(min_index, max_index, array) << std::endl;
    
    find_longest_palindrome_std(size, array, begin_index, end_index);
    if (begin_index == 0 && end_index == 0) {
        std::cout << ">>> В массиве не найдено палиндромов" << std::endl;
    } else {
        std::cout << ">>> Найденный палиндром (индексы " << begin_index << "-" << end_index << "): ";
        output_std_array(array, begin_index, end_index);
    }
    
    quick_sort_std_array(0, size - 1, array);
    std::cout << ">>> Отсортированный массив: ";
    output_std_array(array, 0, size - 1);
}