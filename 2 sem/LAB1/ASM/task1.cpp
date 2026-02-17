#include <cmath>
#include <iostream>

int main() {
    int x, a, b;
    std::cout << "Enter x, a, b: ";
    std::cin >> x >> a >> b;

    int c7 = 7;
    int Y_cpp = (-std::pow(x,3) + a*3 - a + std::pow(x,3) - 2) / (3*std::pow(x,2) - (int)(b/7)) + b;
    int Y_asm;

__asm__ volatile (
        "mov eax, %[x]\n"
        "imul eax, %[x]\n"
        "imul eax, %[x]\n"
        "mov ebx, %[x]\n"
        "imul ebx, %[x]\n"
        "imul ebx, %[x]\n"
        "sub eax, ebx\n"
        "mov ebx, %[a]\n"
        "imul ebx, 3\n"
        "sub ebx, %[a]\n"
        "sub ebx, 2\n"
        "add eax, ebx\n"
        "push eax\n"
        "mov ebx, %[x]\n"
        "imul ebx, %[x]\n"
        "imul ebx, 3\n"
        "mov eax, %[b]\n"
        "cdq\n"
        "idiv %[c7]\n"
        "sub ebx, eax\n"
        "pop eax\n"
        "cdq\n"
        "idiv ebx\n"
        "add eax, %[b]\n"
        "mov %[Y], eax\n"
        : [Y] "=m" (Y_asm)
        : [x] "m" (x),
          [a] "m" (a),
          [b] "m" (b),
          [c7] "m" (c7)
        : "eax", "ebx", "edx"
    );

    std::cout << "C++: " << Y_cpp << std::endl;
    std::cout << "ASM: " << Y_asm << std::endl;
    return 0;
}