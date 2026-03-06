#include "XClass.h"
#include <iostream>

int main () {

    X* Point = new Y(3,4,5);
    int a = Point->run();
    std::cout << a;

}