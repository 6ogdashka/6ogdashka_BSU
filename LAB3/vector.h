#include <iostream>
#include <limits>
#include <cstdint>
#include <ctime>
#include <stdexcept>
#include <vector>
void cin_vector( std::vector<double> &array, int32_t &size);
void cout_vector (std::vector<double> array, int32_t begin, int32_t end);
int get_vector_size (std::vector<double> vector);
double get_double_value();
void random_generate_vector ( std::vector<double>& vector, int32_t size, double left_range_of_elements, double right_range_of_element);
double sum_between_index ( int32_t begin, int32_t end, std::vector<double> vector);
int search_index_of_max_element ( std::vector<double> vector, int32_t size);
int search_index_of_min_element ( std::vector<double> vector, int32_t size);
bool is_vector_are_palindrom ( int32_t begin, int32_t end, std::vector<double> vector);
void search_the_longer_palindrom( int32_t size, std::vector<double> vector, int32_t &begin_index, int32_t &end_index);
void my_right_swap ( int32_t i, std::vector<double>& vector,int32_t &currently_index,int32_t currently_numb);
void my_left_swap ( int32_t i, std::vector<double>& vector, int32_t &currently_index,int32_t currently_numb);
void quick_vector_sort ( int32_t begin_index, int32_t end_index, std::vector<double> &vector);
void input_choice (std::vector<double>& vector, int32_t &size);
void handle_input (std::vector<double>& vector, int32_t &size);
void random_input ( std::vector<double>& vector, int32_t &size); 
void solve ( std::vector<double>& vector, int32_t &size); 
inline void solve_vector () {
    int32_t size{};
    std::vector<double> vector;
    try {
        input_choice(vector,size);
        solve (vector,size);
    } catch ( const char* msg) {
        std::cout << msg;
    }
    return;
}

inline double get_double_value() {
    double value {};
    if (!(std::cin >> value)) {
        throw std::invalid_argument ( " incorrect value " );
    }
    return value;
}

inline int search_index_of_min_element ( std::vector<double> vector, int32_t size ) {
    double min {std::numeric_limits<double>::max()};
    int index {};
    for ( int i{}; i < size; ++i) {
        if ( vector[i] < min) {
            index = i;
            min = vector[i];
        }
    }
    return index;
}

inline int search_index_of_max_element ( std::vector<double> vector, int32_t size) {
    double max{std::numeric_limits<double>::min()};
    int index {};
    for ( int i{}; i < size; ++i) {
        if ( vector[i] > max ) {
            index = i;
            max = vector[i];
        }
    }
    return index;
}

inline double sum_between_index ( int32_t begin, int32_t end, std::vector<double> vector) {
    double sum {};
    if ( begin > end)
    {
    std::swap(begin,end);
    }
    for ( int32_t i {begin}; i <= end; ++i)
    {
        sum += vector[i];
    }
    return sum;
}

inline bool is_vector_are_palindrom(int32_t begin, int32_t end, std::vector<double> vector) {
    for ( int32_t i {0}; i <= ((end-begin)/2); ++i)
    {
        if ( vector[begin + i] == vector[end - i])
        {
            continue;
        }
        else
        {
            return false;
        }
    }
    return true;
}

inline void search_the_longer_palindrom( int32_t size, std::vector<double> vector, int32_t &begin_index, int32_t &end_index) {
    for ( int32_t i {size-1}; i >= 2; --i)
    {
        for ( int32_t j {}; j < (size - i); ++j)
        {
            if ( is_vector_are_palindrom(j,j+i,vector))
            {
                begin_index = j;
                end_index = j + i;
                break;
            }
        }
    }
}

inline void quick_vector_sort ( int32_t begin_index, int32_t end_index, std::vector<double> &vector) {
    int32_t currently_index = static_cast<int>((end_index-begin_index)/2) + begin_index;
    double currently_numb {vector[currently_index]};
    if ( end_index - begin_index < 1)
    {
        return;
    }
    for ( int32_t i {begin_index}; i <=end_index; ++i )
    {
        if ( (vector[i] <= currently_numb) && ( i > currently_index) )
        {
            double temp {vector[currently_index+1]};
            vector[currently_index+1] = vector[i];
            vector[i] = temp;
            vector[currently_index]= vector[currently_index+1];
            vector[currently_index+1]=currently_numb;
            ++currently_index; 
        }
        if ( (vector[i] > currently_numb) && ( i < currently_index))
        {
            vector[currently_index] = vector[i];
            vector[i] = currently_numb;
            currently_index = i;
        }
    }
    if ( currently_index >= 1)
    {
        quick_vector_sort(begin_index, currently_index-1, vector);
    }
    if ( currently_index <= end_index-1)
    {
        quick_vector_sort(currently_index+1,  end_index, vector);
    }
}

inline void cin_vector( std::vector<double> &vector, int32_t &size) {
    double element;
    while ( (std::cin >> element)) {
        vector.push_back(element);
        char ending {0};
        ending = std::cin.get();
        if ( ending == '\n') {
            size = get_vector_size(vector);
            break;
        }
    }
}

inline void handle_input (std::vector<double>& vector, int32_t &size) {
    std::cout << " input your array: ";
    cin_vector(vector,size);
}

inline int get_vector_size (std::vector<double> vector) {
    if ( vector.empty() ) {
        throw std::invalid_argument ( " your vector is empty " );
    }
    return vector.size();
}

inline void cout_vector (std::vector<double> vector,int32_t begin, int32_t end) {
    for ( int i{begin}; i <= end; ++i) {
        std::cout << vector[i] << " ";
    }
    std::cout << std::endl;
}

inline int get_vector_size(int32_t &size) {
    std::cout << " enter array size: ";
    if (!(std::cin >> size)) {
        throw std::invalid_argument(" incorrect size ");
    }
    return size;
}

inline void random_generate_vector(std::vector<double>& vector, int32_t size, double left_range_of_elements, double right_range_of_element ) {
    time_t random_seed {time(NULL)};
    srand(random_seed);
    if ( left_range_of_elements > right_range_of_element) {
        std::swap(left_range_of_elements,right_range_of_element);
    }
    for ( int i{}; i < size; ++i) {
        double range {};
        double coefficent {};
        range = right_range_of_element - left_range_of_elements;
        coefficent = range / static_cast<int>(range);
        vector.push_back(((rand() % static_cast<int>(range*range+1))* 1.0 * coefficent) / ((rand() % static_cast<int>(range))+range) + left_range_of_elements);
    }
}

inline void random_input ( std::vector<double>& vector, int32_t &size) {
    size = get_vector_size(size);
    std::cout << "Введите два числа, которые будут диапазоном(M;N) велечин элементов массива" <<std::endl;
    double left_range_of_elements {get_double_value()};
    double right_range_of_elements {get_double_value()};
    random_generate_vector(vector, size,left_range_of_elements, right_range_of_elements);
    std::cout << " generated array is: ";
    cout_vector(vector,0,size-1);
}

inline void input_choice (std::vector<double>& vector, int32_t &size) {
    //size = get_vector_size(size);
    std::cout << "Выберите формат ввода:" << std::endl;
    std::cout << "Введите еденицу(1),если вы ходите ввести массив с клавиатуры" << std::endl;
    std::cout << "Введите двойку(2), если хотите, чтобы массив был заполнен произвольными числами" << std::endl;
    int32_t numb {};
    std::cin >> numb;
    switch (numb) {
        case 1: {
            handle_input(vector, size);

            break;
        }
        case 2: {
            random_input(vector,size);   
            break;
        }
        default: {
            throw "Вы выбрали неверный формат ввода, выберите его ещё раз более коректно"; 
        }
    }
}
inline void solve ( std::vector<double>& vector, int32_t &size) {
    int32_t index_for_min {search_index_of_min_element(vector,size)};
    int32_t index_for_max {search_index_of_max_element(vector,size)};
    int32_t begin_index{}; 
    int32_t end_index {};
    std::cout << " Sum between the first max element of array and the last minimal element of array is: " 
              << sum_between_index(index_for_min,index_for_max,vector) << std::endl;
    search_the_longer_palindrom(size, vector, begin_index, end_index);
    if ( begin_index == 0 && end_index == 0) { 
        std::cout << " In array there'nt palindrom" << std::endl;
    }
    else {
        std::cout << " the max palindrom is: ";
        cout_vector(vector, begin_index,end_index);
    }
    begin_index = 0;
    end_index = size - 1;
    quick_vector_sort (begin_index,end_index,vector);
    std::cout << " you sorted vector is: ";
    cout_vector(vector, begin_index, end_index);
}