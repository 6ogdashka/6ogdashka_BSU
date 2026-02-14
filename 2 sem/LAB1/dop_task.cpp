#include <iostream>
#include <cmath>
#include <iomanip>

int main() {
    double x;
    std::cout << "Enter x: ";
    std::cin >> x;

    long double base = std::fabsl(std::atanl((long double)x));
    long double exponent = 4.0L * std::cosl((long double)x);
    double Y_cpp = (double)std::pow(base, exponent);
    double Y_asm{};

    __asm__ volatile (
        
    "finit\n"
    "fld QWORD PTR %[x]\n"
    "fld1\n"
    "fpatan\n"
    "fabs\n"

    "fld QWORD PTR %[x]\n"
    "fcos\n"
    "fadd ST(0), ST(0)\n"
    "fxch ST(1)\n"
    "fyl2x\n"

    "fld ST(0)\n" // продублировал степень
    "frndint\n" // получил целую часть

    "fsub ST(1), ST(0)\n" // теперь в st1 находится дробная часть, а в st0 целая
    "fxch ST(1)\n"
    "f2xm1\n"
    "fld1\n"
    "faddp ST(1), ST(0)\n" // получили 2 в степени f, а в st(1) будет лежать целая часть

    "fscale\n"
    "fmul ST(0), ST(0)\n"
    "fstp QWORD PTR %[Y]\n"
    "fstp ST(0)\n" // очистка мусора
    : [Y] "=m" (Y_asm)
    : [x] "m" (x)
    : "st" 
    );
    
    std::cout << std::fixed << std::setprecision(15);
    std::cout << "C++ result: " << (double)Y_cpp << "\n";
    std::cout << "ASM result: " << Y_asm << "\n";

    return 0;
}