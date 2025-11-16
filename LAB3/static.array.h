#include <iostream>
#include <limits>
#include <cstdint>
#include <ctime>
#include <stdexcept>

void input_static_array(double (&array)[MAX_SIZE], int32_t size);
void output_static_array(double array[], int32_t begin, int32_t end);
int get_static_array_size(int32_t &size);
double get_double_value_static();
void generate_random_static_array(double (&array)[MAX_SIZE], int32_t SIZE, double left_range, double right_range);
double sum_between_indices_static(int32_t begin, int32_t end, double array[]);
int find_max_index_static(double array[], int32_t size);
int find_min_index_static(double array[], int32_t size);
bool is_static_array_palindrome(int32_t begin, int32_t end, double array[]);
void find_longest_palindrome_static(int32_t size, double array[], int32_t &begin_index, int32_t &end_index);
void quick_sort_static_array(int32_t begin_index, int32_t end_index, double (&array)[MAX_SIZE]);
void choose_input_method_static(double (&array)[MAX_SIZE], int32_t &size);
void handle_manual_input_static(double (&array)[MAX_SIZE], int32_t size);
void handle_random_input_static(double (&array)[MAX_SIZE], int32_t size);
void process_static_array(double (&array)[MAX_SIZE], int32_t size);

inline void solve_static_array() {
    setRussianLocale();
    
    std::cout << "==============================================================\n";
    std::cout << "|           ПРОГРАММА ДЛЯ РАБОТЫ С МАССИВАМИ               |\n";
    std::cout << "==============================================================\n\n";
    
    int32_t size{};
    double array[MAX_SIZE];
    try {
        choose_input_method_static(array, size);
        process_static_array(array, size);
    } catch (const char* msg) {
        std::cout << "ОШИБКА: " << msg << std::endl;
    } catch (const std::exception& e) {
        std::cout << "ОШИБКА: " << e.what() << std::endl;
    }
    
    std::cout << "\n==============================================================\n";
    std::cout << "|           ПРОГРАММА ЗАВЕРШИЛА РАБОТУ                    |\n";
    std::cout << "==============================================================\n";
    return;
}

inline double get_double_value_static() {
    double value {};
    if (!(std::cin >> value)) {
        throw std::invalid_argument("некорректное значение");
    }
    return value;
}

inline int find_min_index_static(double array[], int32_t size) {
    double min {std::numeric_limits<double>::max()};
    int index {};
    for (int i{}; i < size; ++i) {
        if (array[i] < min) {
            index = i;
            min = array[i];
        }
    }
    return index;
}

inline int find_max_index_static(double array[], int32_t size) {
    double max{std::numeric_limits<double>::min()};
    int index {};
    for (int i{}; i < size; ++i) {
        if (array[i] > max) {
            index = i;
            max = array[i];
        }
    }
    return index;
}

inline double sum_between_indices_static(int32_t begin, int32_t end, double array[]) {
    double sum {};
    if (begin > end) {
        std::swap(begin,end);
    }
    for (int32_t i {begin}; i <= end; ++i) {
        sum += array[i];
    }
    return sum;
}

inline bool is_static_array_palindrome(int32_t begin, int32_t end, double array[]) {
    for (int32_t i {0}; i <= ((end-begin)/2); ++i) {
        if (array[begin + i] == array[end - i]) {
            continue;
        } else {
            return false;
        }
    }
    return true;
}

inline void find_longest_palindrome_static(int32_t size, double array[], int32_t &begin_index, int32_t &end_index) {
    begin_index = 0;
    end_index = 0;
    
    for (int32_t i {size-1}; i >= 1; --i) {
        for (int32_t j {}; j <= (size - i); ++j) {
            if (is_static_array_palindrome(j,j+i,array)) {
                begin_index = j;
                end_index = j + i;
                return;
            }
        }
    }
}

inline void quick_sort_static_array(int32_t begin_index, int32_t end_index, double (&array)[MAX_SIZE]) {
    int32_t currently_index = static_cast<int>((end_index-begin_index)/2) + begin_index;
    double currently_numb {array[currently_index]};
    if (end_index - begin_index < 1) {
        return;
    }
    for (int32_t i {begin_index}; i <=end_index; ++i) {
        if ((array[i] <= currently_numb) && (i > currently_index)) {
            double temp {array[currently_index+1]};
            array[currently_index+1] = array[i];
            array[i] = temp;
            array[currently_index]= array[currently_index+1];
            array[currently_index+1]=currently_numb;
            ++currently_index; 
        }
        if ((array[i] > currently_numb) && (i < currently_index)) {
            array[currently_index] = array[i];
            array[i] = currently_numb;
            currently_index = i;
        }
    }
    if (currently_index >= 1) {
        quick_sort_static_array(begin_index, currently_index-1, array);
    }
    if (currently_index <= end_index-1) {
        quick_sort_static_array(currently_index+1, end_index, array);
    }
}

inline void input_static_array(double (&array)[MAX_SIZE], int32_t size) {
    std::cout << ">>> Введите элементы массива через пробел: ";
    for (int i{}; i < size; ++i) {
        if (!(std::cin >> array[i])) {
            throw std::invalid_argument("некорректное значение элемента");
        }
    }
}

inline void handle_manual_input_static(double (&array)[MAX_SIZE], int32_t size) {
    std::cout << "==============================================================\n";
    std::cout << "|                  РУЧНОЙ ВВОД МАССИВА                     |\n";
    std::cout << "==============================================================\n";
    input_static_array(array, size);
    std::cout << ">>> Массив успешно введен!\n";
}

inline int get_static_array_size(int32_t &size) {
    std::cout << ">>> Введите размер массива (максимум " << MAX_SIZE << "): ";
    if (!(std::cin >> size)) {
        throw std::invalid_argument("некорректный размер");
    }
    if (size <= 0 || size > MAX_SIZE) {
        throw std::invalid_argument("размер должен быть от 1 до " + std::to_string(MAX_SIZE));
    }
    return size;
}

inline void output_static_array(double array[], int32_t begin, int32_t end) {
    std::cout << "[ ";
    for (int i{begin}; i <= end; ++i) {
        std::cout << array[i];
        if (i < end) std::cout << ", ";
    }
    std::cout << " ]" << std::endl;
}

inline void generate_random_static_array(double (&array)[MAX_SIZE], int32_t SIZE, double left_range_of_elements, double right_range_of_element) {
    time_t random_seed {time(NULL)};
    srand(random_seed);
    if (left_range_of_elements > right_range_of_element) {
        std::swap(left_range_of_elements,right_range_of_element);
    }
    for (int i{}; i < SIZE; ++i) {
        double range = right_range_of_element - left_range_of_elements;
        array[i] = left_range_of_elements + (static_cast<double>(rand()) / RAND_MAX) * range;
    }
}

inline void handle_random_input_static(double (&array)[MAX_SIZE], int32_t size) {
    std::cout << "==============================================================\n";
    std::cout << "|               ГЕНЕРАЦИЯ СЛУЧАЙНОГО МАССИВА               |\n";
    std::cout << "==============================================================\n";
    
    size = get_static_array_size(size);
    
    std::cout << "\n==============================================================\n";
    std::cout << "|           ВВЕДИТЕ ДИАПАЗОН ЗНАЧЕНИЙ ЭЛЕМЕНТОВ           |\n";
    std::cout << "==============================================================\n";
    std::cout << ">>> Введите левую границу диапазона: ";
    double left_range_of_elements {get_double_value_static()};
    std::cout << ">>> Введите правую границу диапазона: ";
    double right_range_of_elements {get_double_value_static()};
    
    generate_random_static_array(array, size, left_range_of_elements, right_range_of_elements);
    
    std::cout << "\n>>> Сгенерированный массив: ";
    output_static_array(array, 0, size-1);
}

inline void choose_input_method_static(double (&array)[MAX_SIZE], int32_t &size) {
    std::cout << "==============================================================\n";
    std::cout << "|                   ВЫБЕРИТЕ ФОРМАТ ВВОДА                  |\n";
    std::cout << "==============================================================\n";
    std::cout << "  1 - Ввод массива с клавиатуры\n";
    std::cout << "  2 - Заполнение массива случайными числами\n";
    std::cout << "==============================================================\n";
    std::cout << ">>> Ваш выбор: ";
    
    int32_t numb {};
    std::cin >> numb;
    switch (numb) {
        case 1: {
            handle_manual_input_static(array, size);
            break;
        }
        case 2: {
            handle_random_input_static(array, size);   
            break;
        }
        default: {
            throw "неверный формат ввода. Пожалуйста, выберите 1 или 2"; 
        }
    }
}

inline void process_static_array(double (&array)[MAX_SIZE], int32_t size) {
    std::cout << "\n==============================================================\n";
    std::cout << "|                    РЕЗУЛЬТАТЫ ОБРАБОТКИ                  |\n";
    std::cout << "==============================================================\n";
    
    int32_t index_for_min {find_min_index_static(array, size)};
    int32_t index_for_max {find_max_index_static(array, size)};
    int32_t begin_index{}; 
    int32_t end_index {};
    
    std::cout << ">>> Сумма элементов между минимальным и максимальным элементами: " 
              << sum_between_indices_static(index_for_min, index_for_max, array) << std::endl;
    
    find_longest_palindrome_static(size, array, begin_index, end_index);
    if (begin_index == 0 && end_index == 0) { 
        std::cout << ">>> В массиве нет палиндромов" << std::endl;
    } else {
        std::cout << ">>> Найденный максимальный палиндром: ";
        output_static_array(array, begin_index, end_index);
    }
    
    begin_index = 0;
    end_index = size - 1;
    quick_sort_static_array(begin_index, end_index, array);
    std::cout << ">>> Отсортированный массив: ";
    output_static_array(array, begin_index, end_index);
}