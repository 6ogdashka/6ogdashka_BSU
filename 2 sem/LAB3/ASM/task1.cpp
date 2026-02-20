#include <cmath>
#include <iostream>

int main() {

    std::cout << "Enter x:";
    double x;
    std::cin >> x;
    double Y_cpp;
    double Y_asm;
    double minus7 = -7;
    if ( x < minus7 ) {
        Y_cpp = x - 7;
    } else if ( x > -minus7) {
        Y_cpp = -x + 7;
    } else {
        Y_cpp = std::sqrt(49 - x*x);
    }

    asm (
        "finit\n"
        "fld QWORD PTR %[x]\n"
        "fld QWORD PTR %[minus7]\n"
        "fcompp\n"
        "fstsw ax\n"
        "sahf\n"
        "ja .first_section\n"
        "fld QWORD PTR %[x]\n"
        "fld QWORD PTR %[minus7]\n"
        "fchs\n"
        "fcompp\n"
        "fstsw ax\n"
        "sahf\n"
        "jb .second_section\n"
        ".third_section:\n" // случаи -7 <=    <=7
        "fld QWORD PTR %[x]\n"
        "fmul ST(0), ST(0)\n"
        "fld QWORD PTR %[minus7]\n"
        "fmul ST(0), ST(0)\n"
        "fsub ST(0), ST(1)\n"
        "fsqrt\n"
        "jmp .end_section\n"
        ".first_section:\n" // случаи < -7
        "fld QWORD PTR %[minus7]\n"
        "fchs\n"
        "fld QWORD PTR %[x]\n"
        "fsub ST(0), ST(1)\n"
        "fstp ST(1)\n"
        "jmp .end_section\n" // случаи > 7
        ".second_section:\n"
        "fld QWORD PTR %[x]\n"
        "fld QWORD PTR %[minus7]\n"
        "fchs\n"
        "fsub ST(1)\n"
        "fstp ST(1)\n"
        "jmp .end_section\n"                         
        ".end_section:\n"
        "fstp QWORD PTR %[Y_asm]\n"
        : [Y_asm] "=m" (Y_asm)
        : [x] "m" (x),
          [minus7] "m" (minus7)
        : "ax", "st"

    );

    std::cout << "C++ result:" << Y_cpp << "\n";
    std::cout << "ASM result:" << Y_asm;
}