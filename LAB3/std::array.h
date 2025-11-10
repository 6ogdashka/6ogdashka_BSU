#include <iostream>
#include <limits>
#include <cstdint>
#include <ctime>
#include <stdexcept>
#include <array>
#include "arrays.h"
void cin_array(std::array<double,MAX_SIZE> &array, int32_t size);
void cout_array(std::array<double,MAX_SIZE> array, int32_t begin, int32_t end);
int get_array_size(int32_t &size);
double get_double_value();
void random_generate_array(std::array<double,MAX_SIZE> &array, int32_t SIZE, double left_range_of_elements, double right_range_of_element);
double sum_between_index(int32_t begin, int32_t end, double array[]);
int search_index_of_max_element(std::array<double,MAX_SIZE> array, int32_t size);
int search_index_of_min_element(std::array<double,MAX_SIZE> array, int32_t size);
bool is_array_are_palindrom(int32_t begin, int32_t end, std::array<double,MAX_SIZE> array);
void search_the_longer_palindrom(int32_t size, std::array<double,MAX_SIZE> array, int32_t &begin_index, int32_t &end_index);
void quick_array_sort(int32_t begin_index, int32_t end_index, std::array<double,MAX_SIZE> &array);
void input_choice(std::array<double,MAX_SIZE> &array, int32_t &size);
void handle_input(std::array<double,MAX_SIZE> &array, int32_t size);
void random_input(std::array<double,MAX_SIZE> &array, int32_t size);
void solve(std::array<double,MAX_SIZE> &array, int32_t size);

inline void solve_std_array () {
    int32_t size{};
    std::array<double,MAX_SIZE> array {}; 
    try {
        input_choice(array, size);
        solve(array, size);
    } catch (const char* msg) {
        std::cout << msg;
    } catch (const std::exception& e) {
        std::cout << e.what();
    }
    
    return;
}

inline int search_index_of_min_element(std::array<double,MAX_SIZE> array, int32_t size) {
    double min{std::numeric_limits<double>::max()};
    int index{};
    for (int i{}; i < size; ++i) {
        if (array[i] < min) {
            index = i;
            min = array[i];
        }
    }
    return index;
}

inline int search_index_of_max_element(std::array<double,MAX_SIZE> array, int32_t size) {
    double max{std::numeric_limits<double>::min()};
    int index{};
    for (int i{}; i < size; ++i) {
        if (array[i] > max) {
            index = i;
            max = array[i];
        }
    }
    return index;
}

inline double sum_between_index(int32_t begin, int32_t end, std::array<double,MAX_SIZE> array) {
    double sum{};
    if (begin > end) {
        std::swap(begin, end);
    }
    for (int32_t i{begin}; i <= end; ++i) {
        sum += array[i];
    }
    return sum;
}

inline bool is_array_are_palindrom(int32_t begin, int32_t end, std::array<double,MAX_SIZE> array) {
    for (int32_t i{0}; i <= ((end - begin) / 2); ++i) {
        if (array[begin + i] == array[end - i]) {
            continue;
        } else {
            return false;
        }
    }
    return true;
}

inline void search_the_longer_palindrom(int32_t size, std::array<double,MAX_SIZE> array, int32_t &begin_index, int32_t &end_index) {
    begin_index = 0;
    end_index = 0;
    
    for (int32_t i{size - 1}; i >= 1; --i) {
        for (int32_t j{}; j <= (size - i); ++j) {
            if (is_array_are_palindrom(j, j + i, array)) {
                begin_index = j;
                end_index = j + i;
                return;
            }
        }
    }
}
inline void quick_array_sort ( int32_t begin_index, int32_t end_index, std::array<double,MAX_SIZE> &array) {
    int32_t currently_index = static_cast<int>((end_index-begin_index)/2) + begin_index;
    double currently_numb {array[currently_index]};
    if ( end_index - begin_index < 1) {
        return;
    }
    for ( int32_t i {begin_index}; i <=end_index; ++i ) {
        if ( (array[i] <= currently_numb) && ( i > currently_index) ) {
            double temp {array[currently_index+1]};
            array[currently_index+1] = array[i];
            array[i] = temp;
            array[currently_index]= array[currently_index+1];
            array[currently_index+1]=currently_numb;
            ++currently_index; 
        }
        if ( (array[i] > currently_numb) && ( i < currently_index)) {
            array[currently_index] = array[i];
            array[i] = currently_numb;
            currently_index = i;
        }
    }
    if ( currently_index >= 1) {
        quick_array_sort(begin_index, currently_index-1, array);
    }
    if ( currently_index <= end_index-1) {
        quick_array_sort(currently_index+1,  end_index, array);
    }
}

inline void cin_array(std::array<double,MAX_SIZE> &array, int32_t size){
    for (int i{}; i < size; ++i) {
        if (!(std::cin >> array[i])) {
            throw std::invalid_argument(" one of array element is incorrect ");
        }
    }
}

inline void handle_input(std::array<double,MAX_SIZE> &array, int32_t size) {
    std::cout << " input your array: ";
    cin_array(array, size);
}

inline int get_array_size(int32_t &size) {
    std::cout << " enter array size: ";
    if (!(std::cin >> size)) {
        throw std::invalid_argument(" incorrect size ");
    }
    if (size <= 0 || size > MAX_SIZE) {
        throw " size must be between 1 and " + std::to_string(MAX_SIZE);
    }
    return size;
}

inline void cout_array(std::array<double,MAX_SIZE> array, int32_t begin, int32_t end) {
    for (int i{begin}; i <= end; ++i) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}

inline void random_generate_array(std::array<double,MAX_SIZE> &array, int32_t SIZE, double left_range_of_elements, double right_range_of_element) {
    time_t random_seed{time(NULL)};
    srand(random_seed);
    if (left_range_of_elements > right_range_of_element) {
        std::swap(left_range_of_elements, right_range_of_element);
    }
    for (int i{}; i < SIZE; ++i) {
        double range = right_range_of_element - left_range_of_elements;
        array[i] = left_range_of_elements + (static_cast<double>(rand()) / RAND_MAX) * range;
    }
}

inline void random_input(std::array<double,MAX_SIZE> &array, int32_t size) {
    std::cout << "Введите два числа, которые будут диапазоном(M;N) величин элементов массива" << std::endl;
    double left_range_of_elements{get_double_value()};
    double right_range_of_elements{get_double_value()};
    random_generate_array(array, size, left_range_of_elements, right_range_of_elements);
    std::cout << " generated array is: ";
    cout_array(array, 0, size - 1);
}

inline void input_choice(std::array<double,MAX_SIZE> &array, int32_t &size) {
    size = get_array_size(size);
    std::cout << "Выберите формат ввода:" << std::endl;
    std::cout << "Введите единицу(1), если вы хотите ввести массив с клавиатуры" << std::endl;
    std::cout << "Введите двойку(2), если хотите, чтобы массив был заполнен произвольными числами" << std::endl;
    int32_t numb{};
    std::cin >> numb;
    switch (numb) {
        case 1: {
            handle_input(array, size);
            break;
        }
        case 2: {
            random_input(array, size);
            break;
        }
        default: {
            throw "Вы выбрали неверный формат ввода, выберите его ещё раз более корректно";
        }
    }
}

inline void solve(std::array<double,MAX_SIZE> &array, int32_t size) {
    int32_t index_for_min{search_index_of_min_element(array, size)};
    int32_t index_for_max{search_index_of_max_element(array, size)};
    int32_t begin_index{};
    int32_t end_index{};
    
    std::cout << " Sum between the first max element of array and the last minimal element of array is: "
              << sum_between_index(index_for_min, index_for_max, array) << std::endl;
    
    search_the_longer_palindrom(size, array, begin_index, end_index);
    if (begin_index == 0 && end_index == 0) {
        std::cout << " In array there'nt palindrom" << std::endl;
    } else {
        std::cout << " the max palindrom is: ";
        cout_array(array, begin_index, end_index);
    }
    
    begin_index = 0;
    end_index = size - 1;
    quick_array_sort(begin_index, end_index, array);
    std::cout << " you sorted array is: ";
    cout_array(array, begin_index, end_index);
}