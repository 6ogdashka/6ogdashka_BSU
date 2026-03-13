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
        "jle end_pick\n"
        "dec ecx\n"

        "for_outer:\n"
            "xor edx, edx\n"
            "mov edi, 0\n"
        "findmax:\n"
            "mov eax, [esi + edx*4]\n"
            "mov ebx, [esi + edi*4]\n"
            "cmp eax, ebx\n"
            "jle next_idx\n"
            "mov edi, edx\n"
        "next_idx:\n"
            "inc edx\n"
            "cmp edx, ecx\n"
            "jle findmax\n" 
            
        "mov eax, [esi + ecx*4]\n"
        "mov ebx, [esi + edi*4]\n"
        "mov [esi + ecx*4], ebx\n"
        "mov [esi + edi*4], eax\n" 

        "dec ecx\n"
        "jnz for_outer\n"

        "end_pick:\n"
        ".att_syntax prefix\n"
        :
        : "r" (array), "r" (len)
        : "eax", "ecx", "edx", "esi", "memory"
    );

    for(int i = 0; i < len; ++i) std::cout << array[i] << " ";
    delete[] array;
    return 0;
}