//я буду делать задание 8, потому что задание 6, ну просто нереально простое, самое простое среди всех.
#include <iostream>
#include <math.h>


int main() {

    double x,y;
    std::cout << "Enter x,y: ";
    std::cin >> x >> y;

    // x = fmod(x,2.0*acos(-1.0));
    // y = fmod(y,2.0*acos(-1));

    // if (x < y) { std::swap(x,y);}

    double Y_cpp = (std::pow((abs(1.0 - tan(x))),(1/tan(x))) + cos(x-y)); // модуль, потому что нельзя возводить отрицательные числа в дробную степень
    double Y_asm{};

    __asm__ volatile (
        "finit\n"
        "fld QWORD PTR %[x]\n"
        "fcos\n"
        "fld QWORD PTR %[x]\n"
        "fsin\n"
        "fdiv ST(1)\n"
        "fld1\n"
        "fsub ST(1)\n"
        "fxch ST(2)\n"
        "fstp ST(0)\n"
        "fld1\n"
        "fdiv ST(1)\n"
        "fxch ST(1)\n"
        "fstp ST(0)\n"
        "fxch ST(1)\n"
        "fabs\n"
        "fyl2x\n" // нужная степень в ST(0)
        "fld1\n"
        "fscale\n"
        "fxch ST(1)\n"
        "fld ST(0)\n"
        "frndint\n"
        "fsub ST(1),ST(0)\n"
        "fstp ST(0)\n"
        "f2xm1\n"
        "fld1\n"
        "fadd ST(0),ST(1)\n"
        "fxch ST(1)\n"
        "fstp ST(0)\n"
        "fmul ST(0), ST(1)\n"
        "fxch ST(1)\n"
        "fstp ST(0)\n" // получили тангенс 
        "fld QWORD PTR %[y]\n"
        "fld QWORD PTR %[x]\n"
        "fsub ST(1)\n"
        "fcos\n"
        "fadd ST(2)\n"
        "fxch ST(2)\n" // очистка
        "fstp ST(0)\n"
        "fstp ST(0)\n"
        "fstp QWORD PTR %[Y]\n"
        : [Y] "=m" (Y_asm)
        : [x] "m" (x),
          [y] "m" (y)
        : "st"
    );

    std::cout << "C++ result:" << Y_cpp << "\n";
    std::cout << "ASM result:" << Y_asm; 
}