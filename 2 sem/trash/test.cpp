#include <cmath>
#include <iostream>

int main() {
    double R, y1, y2;
    double x = 4.0, c4 = 4.0, c2 = 2.0;

    std::cout << "C++ " << cos(x * x / 4.0 + sqrt(x / 2.0 + 1.0)) << std::endl;

    __asm__ volatile (
        "finit\n"
        "fld QWORD PTR %[x]\n"
        "fmul QWORD PTR %[x]\n"
        "fdiv QWORD PTR %[c4]\n"
        "fstp QWORD PTR %[y1]\n"
        "fld QWORD PTR %[x]\n"
        "fdiv QWORD PTR %[c2]\n"
        "fstp QWORD PTR %[y2]\n"
        "fld1\n"
        "fadd QWORD PTR %[y2]\n"
        "fsqrt\n"
        "fadd QWORD PTR %[y1]\n"
        "fcos\n"
        "fstp QWORD PTR %[R]\n"
        : [R] "=m" (R),
          [y1] "=m" (y1),
          [y2] "=m" (y2)
        : [x] "m" (x),
          [c4] "m" (c4),
          [c2] "m" (c2)
        : "st"
    );

    std::cout << "asm= " << R << std::endl;
    return 0;
}