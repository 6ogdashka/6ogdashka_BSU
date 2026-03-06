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
        "mov rbx, %[arr]\n"
        "mov rdx, %[len_ptr]\n"
        "xor rcx, rcx\n"

        "loop_start:\n"
        "mov eax, [rdx]\n"
        "cdqe\n"
        "cmp rcx, rax\n"
        "jge loop_end\n"

        "mov eax, [rbx + rcx*4]\n"
        "test eax, 1\n"
        "jnz next_step\n"

        "mov r12d, eax\n"
        "xor edi, edi\n"
        "mov r10d, 10\n"

        "rev_loop:\n"
        "test r12d, r12d\n"
        "jz rev_done\n"
        "xor edx, edx\n"
        "mov eax, r12d\n"
        "div r10d\n"
        "mov r12d, eax\n"
        "imul edi, 10\n"
        "add edi, edx\n"
        "jmp rev_loop\n"

        "rev_done:\n"
        "mov rdx, %[len_ptr]\n"
        "mov eax, [rdx]\n"
        "cdqe\n"
        "mov rsi, rax\n"
        "mov rax, rax\n"
        "dec rsi\n"

        "shift_loop:\n"
        "cmp rax, rcx\n"
        "jle shift_done\n"
        "mov r12d, [rbx + rsi*4]\n"
        "mov [rbx + rax*4], r12d\n"
        "dec rax\n"
        "dec rsi\n"
        "jmp shift_loop\n"

        "shift_done:\n"
        "mov [rbx + rcx*4 + 4], edi\n"
        "inc dword ptr [rdx]\n"
        "inc rcx\n"

        "next_step:\n"
        "inc rcx\n"
        "mov rdx, %[len_ptr]\n"
        "jmp loop_start\n"

        "loop_end:\n"
        ".att_syntax prefix\n"
        :
        : [arr] "r" (arr), [len_ptr] "r" (&len)
        : "rax", "rbx", "rcx", "rdx", "rsi", "rdi", "r10", "r12", "memory"
    );

    std::cout << "Результат: ";
    for (int i = 0; i < len; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    delete[] arr;
    return 0;
}