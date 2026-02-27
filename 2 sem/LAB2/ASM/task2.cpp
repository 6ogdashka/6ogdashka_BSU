#include <iostream>
#include <algorithm>

int main() {
    int a, b, c, d;
    std::cout << "Размеры коробки (a b): ";
    std::cin >> a >> b;
    std::cout << "Размеры пирожного (c d): ";
    std::cin >> c >> d;

    int b_max = std::max(a, b);
    int b_min = std::min(a, b);
    int c_max = std::max(c, d);
    int c_min = std::min(c, d);

    int res1 = 0, res2 = 0;
    __asm__  volatile (    

        "mov eax, %[b_min]\n"
        "xor edx, edx\n"       
        "div %[c_max]\n"
        "mov ecx, eax\n"

        "mov eax, %[b_max]\n"
        "xor edx, edx\n"        
        "div %[c_min]\n"
        "imul eax, ecx\n"
        "mov %[r2], eax\n"

        "mov eax, %[b_max]\n"
        "xor edx, edx\n"       
        "div %[c_max]\n"
        "mov ecx, eax\n"

        "mov eax, %[b_min]\n"
        "xor edx, edx\n"       
        "div %[c_min]\n"
        "imul eax, ecx\n"   
        "mov %[r1], eax\n"

        : [r1] "=m" (res1),[r2] "=m" (res2)
        : [b_max] "r" (b_max), [b_min] "r" (b_min), 
          [c_max] "r" (c_max), [c_min] "r" (c_min)
        : "eax", "edx", "ecx", "cc"
    );

    std::cout << "Результат вдоль длинной стороны:" << res1 << std::endl;
    std::cout << "Результат вдоль коротной стороны:" << res2 << std::endl;


    return 0;
}