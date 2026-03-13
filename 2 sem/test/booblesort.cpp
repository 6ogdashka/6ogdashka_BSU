#include <iostream>

int main() {
    int* array = new int[100];
    int len{};
    if (!(std::cin >> len)) return 0;
    for(int i{}; i < len; ++i) {
        std::cin >> array[i];
    }

    __asm__ volatile (
        ".intel_syntax noprefix\n"

        "mov esi, %0\n"
        "mov ecx, %1\n"
        "cmp ecx, 1\n"
        "jle end_bubble\n"
        "dec ecx\n"
        
        "for1:\n"
        "xor edx, edx\n"
        
        "for2:\n"
        "mov eax, [esi + edx*4]\n"
        "mov ebx, [esi + edx*4 + 4]\n"
        "cmp eax, ebx\n"
        "jle no_swap\n"
        
        "mov [esi + edx*4], ebx\n"
        "mov [esi + edx*4 + 4], eax\n"
        
        "no_swap:\n"
        "inc edx\n"
        "cmp edx, ecx\n"
        "jl for2\n"
        
        "dec ecx\n"
        "jnz for1\n"
        
        "end_bubble:\n"
        "pop ebx\n"
        ".att_syntax prefix\n"
        :
        : "r" (array), "r" (len)
        : "eax", "ecx", "edx", "esi", "memory"
    );

    for(int i = 0; i < len; ++i) std::cout << array[i] << " ";
    delete[] array;
    return 0;
}