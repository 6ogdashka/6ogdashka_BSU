#include <cmath>
#include <algorithm>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include "russian.h"

class Function {
    public:
    virtual double operator() (double x) = 0;
};
class Function1 : public Function {
    public:
     double operator() (double x) override {
        return x*(sqrt(x + 1));
    }
};

class Function2 : public Function {
    double operator() (double x) override {
        return asin(sqrt(x)) / sqrt(x * (1 - x));
    }
};

class Function3 : public Function {
    double operator() (double x) override {
        return pow(2, x) / (1 + pow(4, x));
    }
};
double get_double_value(); 
double left_rectangle_method(
    Function* f, double low_limit, double high_limit,
    const double exactness);
double right_rectangle_method(
    Function* f, double low_limit, double high_limit,
    const double exactness); 
double middel_rectangle_method(
    Function* f, double low_limit, double high_limit,
    const double exactness);
double trapezoid_method(
    Function* f, double low_limit, double high_limit,
    const double exactness); 
double Simpson_method ( Function* f, double low_limit, double high_limit); 

int main() {
    setRussianLocale();
    try {
    std::cout << "Выберите функцию для интегрирования:\n";
    std::cout << "1. x·√(1-x) \n";
    std::cout << "2. arcsin(√x)/√(x(1-x)) \n";
    std::cout << "3. 2ˣ/(1+4ˣ) \n";
    
    int32_t choice;
    std::cin >> choice;
    
    Function* p = nullptr;
    switch (choice) {
        case 1: {
            p = new Function1();
            break;
        }
        case 2: {
            p = new Function2();
            break;
        }
        case 3: {
            p = new Function3();
            break;
        }
        default: {
            delete p;
            throw "Неверный выбор функции!\n";
        }
    }

    std::cout << "\nВыберите метод интегрирования:\n";
    std::cout << "1. Метод левых прямоугольников\n";
    std::cout << "2. Метод правых прямоугольников\n";
    std::cout << "3. Метод средних прямоугольников\n";
    std::cout << "4. Метод трапеций\n";
    std::cout << "5. Метод Симпсона\n";
    
    int32_t method_choice;
    std::cin >> method_choice;

    double low_limit, high_limit, exactness;
    std::cout << "\nВведите нижний предел интегрирования: ";
    low_limit = get_double_value();
    std::cout << "Введите верхний предел интегрирования: ";
    high_limit = get_double_value();
    std::cout << "Введите точность: ";
    exactness = get_double_value();

    double result = 0.0;
    switch (method_choice) {
        case 1: {
            result = left_rectangle_method(p, low_limit, high_limit, exactness);
            break;
        }
        case 2: {
            result = right_rectangle_method(p, low_limit, high_limit, exactness);
            break;
        }
        case 3: {
            result = middel_rectangle_method(p, low_limit, high_limit, exactness);
            break;
        }
        case 4: {
            result = trapezoid_method(p, low_limit, high_limit, exactness);
            break;
        }
        case 5: {
            result = Simpson_method(p, low_limit, high_limit);
            break;
        }
        default: {
            delete p;
            throw  "Неверный выбор метода!\n";
        }
    }
    std::cout << std::setprecision( 30);
    std::cout << "\nРезультат интегрирования: " << result << std::endl;
    delete p;
    } catch ( const char* msg) { std::cout << msg; }
    return 0;
}

double get_double_value() {
    double value {};
    if (!(std::cin >> value)) {
        throw std::invalid_argument("некорректное значение");
    }
    return value;
}

double left_rectangle_method(
    Function* f, double low_limit, double high_limit,
    const double exactness) {
        double result{1};
        double previus_result{0};
        if ( (high_limit - low_limit) < 0.000001 ) {
            std::swap(low_limit,high_limit);
        }
        int32_t n{4};
        double range {high_limit - low_limit};
        while ( std::abs(previus_result - result) > exactness) {
            double current_result {};
            for ( int32_t i {0}; i < n; ++i) {
                 double x_i = low_limit + (i * range / n);
                 current_result += ((*f)(x_i)* (range / n));
                 previus_result = current_result;
            }
            current_result = 0;
            for ( int32_t i {0}; i < 2*n; ++i) {
                 double x_i = low_limit + (i * range / (2*n));
                 current_result += ((*f)(x_i)* (range / (2*n)));
                 result = current_result;
            }
            n *= 2;
        }
        return result;
}

double right_rectangle_method(
    Function* f, double low_limit, double high_limit,
    const double exactness) {
        double result{1};
        double previus_result{0};
        if ( (high_limit - low_limit) < 0.000001 ) {
            std::swap(low_limit,high_limit);
        }
        int32_t n{4};
        double range {high_limit - low_limit};
        while ( std::abs(previus_result - result) > exactness) {
            double current_result {};
            for ( int32_t i {1}; i <= n; ++i) {
                 double x_i = low_limit + (i * range / n);
                 current_result += ((*f)(x_i)* (range / n));
                 previus_result = current_result;
            }
            current_result = 0;
            for ( int32_t i {1}; i <= 2*n; ++i) {
                 double x_i = low_limit + (i * range / (2*n));
                 current_result += ((*f)(x_i)* (range / (2*n)));
                 result = current_result;
            }
            n *= 2;
        }
        return result;
}

double middel_rectangle_method(
    Function* f, double low_limit, double high_limit,
    const double exactness) {
        double result{1};
        double previus_result{0};
        if ( (high_limit - low_limit) < 0.000001 ) {
            std::swap(low_limit,high_limit);
        }
        int32_t n{4};
        double range {high_limit - low_limit};
        while ( std::abs(result - previus_result) > exactness) {
            double current_result {};
            for ( int32_t i {0}; i < n; ++i) {
                 double x_i = low_limit + (i * range / n);
                 double x_i1 = low_limit + ( (i+1) * range / n);
                 current_result += (((*f)((x_i + x_i1)/2))* (range / n));
                 previus_result = current_result;
            }
            current_result = 0;
            for ( int32_t i {0}; i < 2*n; ++i) {
                 double x_i = low_limit + (i * range / (2*n));
                 double x_i1 = low_limit + ( (i+1) * range / (2*n));
                 current_result += (((*f)((x_i + x_i1)/2))* (range / (2*n)));
                 result = current_result;
            }
            n *= 2;
        }
        return result;
}

double trapezoid_method(
    Function* f, double low_limit, double high_limit,
    const double exactness) {
        double result{1};
        double previus_result{0};
        if ( (high_limit - low_limit) < 0.000001 ) {
            std::swap(low_limit,high_limit);
        }
        int32_t n{4};
        double range {high_limit - low_limit};
        while ( std::abs(result - previus_result) > exactness) {
            double current_result {};
            for ( int32_t i {0}; i < n; ++i) {
                 double x_i = low_limit + (i * range / n);
                 double x_i1 = low_limit + ( (i+1) * range / n);
                 current_result += ((((*f)(x_i) + (*f)(x_i1))/2)* (range / n));
                 previus_result = current_result;
            }
            current_result = 0;
            for ( int32_t i {0}; i < 2*n; ++i) {
                 double x_i = low_limit + (i * range / (2*n));
                 double x_i1 = low_limit + ( (i+1) * range / (2*n));
                 current_result += ((((*f)(x_i) + (*f)(x_i1))/2)* (range / (2*n)));
                 result = current_result;
            }
            n *= 2;
        }
        return result;
}

double Simpson_method ( Function* f, double low_limit, double high_limit) {
    double result{};
    if ( (high_limit - low_limit) < 0.000001 ) {
        std::swap(low_limit,high_limit);
    }
    result = ((high_limit - low_limit) / 6) * ((*f)(low_limit) + 4 * (*f) ( (low_limit + high_limit) / 2) + (*f)(high_limit));
    return result;
}




