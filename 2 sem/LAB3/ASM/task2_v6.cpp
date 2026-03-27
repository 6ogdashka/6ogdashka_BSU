#include <iostream>

int main() {
    int* arr = new int[100];
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
        "dec    eax\n"
        "cmp    rcx, rax\n"
        "jge    main_loop_end\n"

        "mov    r8d, [rbx + rcx*4]\n"
        "mov    r9d, [rbx + rcx*4 + 4]\n"
        "cmp    r8d, r9d\n"
        "jne    next_i\n"

        "mov    rsi, rcx\n"
        "inc    rsi\n"
        "mov    rdi, rsi\n"
        "inc    rdi\n"

        "shift_loop:\n"
        "mov    eax, [rdx]\n"
        "cmp    rdi, rax\n"
        "jge    shift_done\n"
        "mov    r10d, [rbx + rdi*4]\n"
        "mov    [rbx + rsi*4], r10d\n"
        "inc    rsi\n"
        "inc    rdi\n"
        "jmp    shift_loop\n"

        "shift_done:\n"
        "sub    dword ptr [rdx], 1\n"
        "jmp    main_loop\n"

        "next_i:\n"
        "inc    rcx\n"
        "jmp    main_loop\n"

        "main_loop_end:\n"
        ".att_syntax prefix\n"
        :
        : [arr] "r" (arr), [len_ptr] "r" (&len)
        : "rax", "rbx", "rcx", "rdx", "rsi", "rdi", "r8", "r9", "r10", "memory"
    );

    std::cout << "Результат: ";
    for (int i = 0; i < len; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    delete[] arr;
    return 0;
}