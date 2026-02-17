#include <iostream>
#include "V6.h"

int main() {

    Inherited Point(3,4,5);
    std::cout << Point.Run() << "\n";
    Point.Show();
    
}