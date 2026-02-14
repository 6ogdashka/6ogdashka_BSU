#include <iostream>
#include <math.h>


int main() {

    double x;
    std::cout << "Enter x: ";
    std::cin >> x;

    double Y_cpp = std::pow((double)std::pow(std::abs(atan(x)),2.0*cos(x)),2.0);
    double Y_asm{};

    __asm__ volatile (
        "finit\n"
        "fld QWORD PTR %[x]\n"
        "fld1\n"
        "fpatan\n"
        "fabs\n"
        "fld QWORD PTR %[x]\n"
        "fcos\n"
        "fxch ST(1)\n"
        "fyl2x\n"
        "fadd ST(0)\n"
        "fld1\n"
        "fscale\n"
        "fxch ST(1)\n"
        "fld ST(0)\n"
        "frndint\n"
        "fsub ST(1),ST(0)\n"
        "fstp ST(0)\n"
        "f2xm1\n"
        "fld1\n"
        "fadd ST(1),ST(0)\n"
        "fstp ST(0)\n"
        "fmul ST(0),ST(1)\n"
        "fstp ST(1)\n"
        "fmul ST(0)\n"
        "fstp QWORD PTR %[Y]\n"
        : [Y] "=m" (Y_asm)
        : [x] "m" (x)
        : "st"
    );
    
    std::cout << "C++ result:" << Y_cpp << "\n";
    std::cout << "ASM result:" << Y_asm << "\n";
}