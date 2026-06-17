#include <cmath>
#include <cstdint>
#include <iomanip>
#include <iostream>

extern "C" double calc_func(double x);

class Function {
public:
    virtual double operator() (double x) = 0;
    virtual ~Function() {}
};

class Function1 : public Function {
public:
    double operator() (double x) override {
        return x * (sqrt(x + 1));
    }
};

class Function2 : public Function {
public:
    double operator() (double x) override {
        if (x <= 0.0) return 0.0;
        if (x >= 1.0) x = 0.99999999; //asin(sqrt(x)) / sqrt(x * (1 - x)) 
        return calc_func(x);
    }
};

class Function3 : public Function {
public:
    double operator() (double x) override {
        return pow(2, x) / (1 + pow(4, x));
    }
};

double get_double_value();
int get_int_value();
double left_rectangle_method(Function* f, double low_limit, double high_limit, const double exactness);
double right_rectangle_method(Function* f, double low_limit, double high_limit, const double exactness);
double middel_rectangle_method(Function* f, double low_limit, double high_limit, const double exactness);
double trapezoid_method(Function* f, double low_limit, double high_limit, const double exactness);
double Simpson_method(Function* f, double low_limit, double high_limit);

int main() {
    try {
        std::cout << "Выберите функцию для интегрирования:\n";
        std::cout << "1. x·√(x+1) \n";
        std::cout << "2. arcsin(√x)/√(x(1-x)) \n";
        std::cout << "3. 2ˣ/(1+4ˣ) \n";

        int32_t choice;
        if (!(std::cin >> choice)) throw "Ошибка ввода\n";

        Function* p = nullptr;
        switch (choice) {
            case 1: p = new Function1(); break;
            case 2: p = new Function2(); break;
            case 3: p = new Function3(); break;
            default: throw "Неверный выбор функции!\n";
        }

        std::cout << "\nВыберите метод:\n1. Левые\n2. Правые\n3. Средние\n4. Трапеции\n5. Симпсон\n";
        int32_t method_choice = get_int_value();

        double low_limit, high_limit, exactness;
        std::cout << "Нижний предел: "; low_limit = get_double_value();
        std::cout << "Верхний предел: "; high_limit = get_double_value();
        std::cout << "Точность: "; exactness = get_double_value();

        double result = 0.0;
        switch (method_choice) {
            case 1: result = left_rectangle_method(p, low_limit, high_limit, exactness); break;
            case 2: result = right_rectangle_method(p, low_limit, high_limit, exactness); break;
            case 3: result = middel_rectangle_method(p, low_limit, high_limit, exactness); break;
            case 4: result = trapezoid_method(p, low_limit, high_limit, exactness); break;
            case 5: result = Simpson_method(p, low_limit, high_limit); break;
            default: delete p; throw "Неверный выбор метода!\n";
        }

        std::cout << std::fixed << std::setprecision(exactness);
        std::cout << "\nРезультат: " << result << std::endl;
        delete p;
    } catch (const char* msg) { std::cout << msg; }
    catch (const std::exception& e) { std::cout << e.what() << std::endl; }
    return 0;
}

double get_double_value() {
    double value;
    if (!(std::cin >> value)) throw std::invalid_argument("некорректное значение");
    return value;
}

int get_int_value() {
    int value;
    if (!(std::cin >> value)) throw std::invalid_argument("некорректное значение");
    return value;
}

double left_rectangle_method(Function* f, double low_limit, double high_limit, const double exactness) {
    double result = 1e10, previus_result = 0;
    int32_t n = 4;
    double range = high_limit - low_limit;
    while (std::abs(result - previus_result) > exactness) {
        previus_result = result;
        double current_result = 0;
        for (int32_t i = 0; i < n; ++i) {
            current_result += (*f)(low_limit + i * range / n);
        }
        result = current_result * (range / n);
        n *= 2;
    }
    return result;
}

double right_rectangle_method(Function* f, double low_limit, double high_limit, const double exactness) {
    double result = 1e10, previus_result = 0;
    int32_t n = 4;
    double range = high_limit - low_limit;
    while (std::abs(result - previus_result) > exactness) {
        previus_result = result;
        double current_result = 0;
        for (int32_t i = 1; i <= n; ++i) {
            current_result += (*f)(low_limit + i * range / n);
        }
        result = current_result * (range / n);
        n *= 2;
    }
    return result;
}

double middel_rectangle_method(Function* f, double low_limit, double high_limit, const double exactness) {
    double result = 1e10, previus_result = 0;
    int32_t n = 4;
    double range = high_limit - low_limit;
    while (std::abs(result - previus_result) > exactness) {
        previus_result = result;
        double current_result = 0;
        double h = range / n;
        for (int32_t i = 0; i < n; ++i) {
            current_result += (*f)(low_limit + h * (i + 0.5));
        }
        result = current_result * h;
        n *= 2;
    }
    return result;
}

double trapezoid_method(Function* f, double low_limit, double high_limit, const double exactness) {
    double result = 1e10, previus_result = 0;
    int32_t n = 4;
    double range = high_limit - low_limit;
    while (std::abs(result - previus_result) > exactness) {
        previus_result = result;
        double h = range / n;
        double current_result = ((*f)(low_limit) + (*f)(high_limit)) / 2.0;
        for (int32_t i = 1; i < n; ++i) {
            current_result += (*f)(low_limit + i * h);
        }
        result = current_result * h;
        n *= 2;
    }
    return result;
}

double Simpson_method(Function* f, double low_limit, double high_limit) {
    return ((high_limit - low_limit) / 6.0) * ((*f)(low_limit) + 4.0 * (*f)((low_limit + high_limit) / 2.0) + (*f)(high_limit));
}