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
        "mov rbx, %[arr]\n"
        "mov rdx, %[len_ptr]\n"
        "xor rcx, rcx\n"

        "loop_start: \n"              // i < len-1
        "mov eax, [rdx]\n"
        "cdqe\n"
        "dec rax\n"
        "cmp rcx, rax\n"
        "jge loop_end\n"

        "mov r8d, [rbx + rcx*4]\n"    // Сравнение
        "mov r9d, [rbx + rcx*4 + 4]\n"
        "cmp r8d, r9d\n"
        "jne next_step\n"

        "mov rsi, rcx\n"              // Сдвиги
        "inc rsi\n"
        "mov rdi, rsi\n"
        "inc rsi\n"

        "shift_loop: \n"              // основной цикл Цикл 
        "mov eax, [rdx]\n"
        "cdqe\n"
        "cmp rdi, rax\n"
        "jge shift_done\n"
        "mov r10d, [rbx + rsi*4]\n"
        "mov [rbx + rdi*4], r10d\n"
        "inc rsi\n"
        "inc rdi\n"
        "jmp shift_loop\n"

        "shift_done: \n"           
        "sub dword ptr [rdx], 1\n"
        "jmp loop_start\n"

        "next_step: \n"               // Следуйщий индекс
        "inc rcx\n"
        "jmp loop_start\n"

        "loop_end: \n"
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