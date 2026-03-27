#include <iostream>

int main() {
    int x[] = {1, 5, 10, 20};
    int y[] = {2, 5, 15, 25};
    int z[] = {3, 4, 5, 30};
    int n = 4, m = 4, d = 4;
    int result = -1;

    __asm__ volatile (
        ".intel_syntax noprefix\n"
        "xor    r8d, r8d\n"
        "xor    r9d, r9d\n"
        "xor    r10d, r10d\n"

        "find_loop:\n"
        "mov    eax, %[n]\n"
        "cmp    r8d, eax\n"
        "jge    not_found\n"
        "mov    eax, %[m]\n"
        "cmp    r9d, eax\n"
        "jge    not_found\n"
        "mov    eax, %[d]\n"
        "cmp    r10d, eax\n"
        "jge    not_found\n"

        "mov    eax, [%[x_ptr] + r8*4]\n"
        "mov    ebx, [%[y_ptr] + r9*4]\n"
        "mov    ecx, [%[z_ptr] + r10*4]\n"

        "cmp    eax, ebx\n"
        "jl     inc_i\n"
        "jg     inc_j\n"

        "cmp    eax, ecx\n"
        "jl     inc_k\n"
        "jg     inc_k\n"

        "mov    %[res], eax\n"
        "jmp    loop_end\n"

        "inc_i:\n"
        "inc    r8d\n"
        "jmp    find_loop\n"

        "inc_j:\n"
        "inc    r9d\n"
        "jmp    find_loop\n"

        "inc_k:\n"
        "inc    r10d\n"
        "jmp    find_loop\n"

        "not_found:\n"

        "loop_end:\n"
        ".att_syntax prefix\n"
        : [res] "=r" (result)
        : [x_ptr] "r" (x), [y_ptr] "r" (y), [z_ptr] "r" (z),
          [n] "r" (n), [m] "r" (m), [d] "r" (d)
        : "rax", "rbx", "rcx", "r8", "r9", "r10", "memory"
    );

    if (result != -1)
        std::cout << "Общее число: " << result << std::endl;
    else
        std::cout << "Общих чисел нет" << std::endl;

    return 0;
}