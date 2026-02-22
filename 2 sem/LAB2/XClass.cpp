#include "XClass.h"

X::X(int a, int b) : x1(a), x2(b) {}

X::~X() {}

void X::show() const {
    std::cout << "X: x1 = " << x1 << ", x2 = " << x2 << std::endl;
}

void X::set(int a, int b) {
    x1 = a;
    x2 = b;
}

int X::run() const{
    return 0;
}

Y::Y(int a, int b, int c) : X(a, b), y(c) {}

Y::~Y() {}

void Y::show() const {
    std::cout << "Y: x1 = " << x1 << ", x2 = " << x2 << ", y = " << y << std::endl;
}

void Y::set(int a, int b) {
    X::set(a, b); 
}

void Y::setY(int newY) {
    y = newY;
}

int Y::run() const {
    return (x1 + x2) * y;
}
