#include <iostream>

int main() {
    int* arr = new int[200];
    int len{};

    std::cout << "Введите размер массива: ";
    std::cin >> len;
    std::cout << "Введите элементы массива: ";
    for (int i = 0; i < len; ++i) {
        std::cin >> arr[i];
    }

    __asm__ volatile (
        ".intel_syntax noprefix\n"
        "mov    rbx, %[arr]\n"
        "mov    rdx, %[len_ptr]\n"
        "xor    rcx, rcx\n"

        "main_loop:\n"
        "mov    eax, [rdx]\n"
        "cmp    rcx, rax\n"
        "jge    main_loop_end\n"

        "mov    eax, [rbx + rcx*4]\n"
        "test   eax, 1\n"
        "jnz    next_i\n"

        "mov    r8d, eax\n"
        "xor    r9d, r9d\n"
        "mov    r10d, 10\n"

        "reverse_loop:\n"
        "test   r8d, r8d\n"
        "jz     reverse_done\n"
        "xor    edx, edx\n"
        "mov    eax, r8d\n"
        "div    r10d\n"
        "mov    r8d, eax\n"
        "imul   r9d, 10\n"
        "add    r9d, edx\n"
        "jmp    reverse_loop\n"

        "reverse_done:\n"
        "mov    r11d, [rdx]\n"
        "mov    r12, r11\n"
        "mov    r13, r11\n"
        "dec    r13\n"
        "mov    r14, rcx\n"
        "inc    r14\n"

        "shift_loop:\n"
        "cmp    r13, r14\n"
        "jl     shift_done\n"
        "mov    r15d, [rbx + r13*4]\n"
        "mov    [rbx + r13*4 + 4], r15d\n"
        "dec    r13\n"
        "jmp    shift_loop\n"

        "shift_done:\n"
        "mov    [rbx + r14*4], r9d\n"
        "inc    dword ptr [rdx]\n"
        "add    rcx, 2\n"
        "jmp    main_loop\n"

        "next_i:\n"
        "inc    rcx\n"
        "jmp    main_loop\n"

        "main_loop_end:\n"
        ".att_syntax prefix\n"
        :
        : [arr] "r" (arr), [len_ptr] "r" (&len)
        : "rax", "rbx", "rcx", "rdx", "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15", "memory"
    );

    for (int i = 0; i < len; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    delete[] arr;
    return 0;
}