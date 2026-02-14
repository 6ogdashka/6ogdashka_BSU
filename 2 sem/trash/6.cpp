#include <cmath>
#include <iostream>

int main() {
    double x, a, b;
    std::cout << "Enter x, a, b: ";
    std::cin >> x >> a >> b;

    double c2 = 2.0, c3 = 3.0, c7 = 7.0;
    double Y_cpp = (-std::pow(x,3) + a*3 - a + std::pow(x,3) - 2) / (3*std::pow(x,2) - b/7) + b;
    double Y_asm;

    __asm__ volatile (
        "finit\n"
        "fld QWORD PTR %[x]\n"
        "fmul QWORD PTR %[x]\n"
        "fmul QWORD PTR %[x]\n"
        "fld %%st(0)\n"
        "fchs\n"
        "fld QWORD PTR %[a]\n"
        "fld QWORD PTR %[c3]\n"
        "fmulp\n"
        "faddp\n"
        "fld QWORD PTR %[a]\n"
        "fsubp\n"
        "faddp\n"
        "fld QWORD PTR %[c2]\n"
        "fsubp\n"
        "fld QWORD PTR %[x]\n"
        "fmul QWORD PTR %[x]\n"
        "fld QWORD PTR %[c3]\n"
        "fmulp\n"
        "fld QWORD PTR %[b]\n"
        "fld QWORD PTR %[c7]\n"
        "fdivp\n"
        "fsubp\n"
        "fdivp\n"
        "fadd QWORD PTR %[b]\n"
        "fstp QWORD PTR %[Y]\n"
        : [Y] "=m" (Y_asm)
        : [x] "m" (x), [a] "m" (a), [b] "m" (b),
          [c2] "m" (c2), [c3] "m" (c3), [c7] "m" (c7)
        : "st"
    );

    std::cout << "C++: " << Y_cpp << std::endl;
    std::cout << "ASM: " << Y_asm << std::endl;
    return 0;
}