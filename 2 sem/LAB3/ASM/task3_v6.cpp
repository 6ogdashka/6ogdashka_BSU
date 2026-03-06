#include <iostream>

int main() {
    int x[] = {1, 5, 10, 20};
    int y[] = {2, 5, 15, 25};
    int z[] = {3, 4, 5, 30};
    int n = 4, m = 4, d = 4;
    int result = -1;

    __asm__ volatile (
        ".intel_syntax noprefix\n"
        "xor r8, r8\n"              // Инициализация указателей i, j, k нулями
        "xor r9, r9\n"
        "xor r10, r10\n"

        "find_loop:\n"              // Проверка выхода за границы всех трех массивов
        "mov eax, %[n]\n"
        "cmp r8d, eax\n"
        "jge not_found\n"
        "mov eax, %[m]\n"
        "cmp r9d, eax\n"
        "jge not_found\n"
        "mov eax, %[d]\n"
        "cmp r10d, eax\n"
        "jge not_found\n"

        "mov eax, [%[x_ptr] + r8*4]\n" // Загрузка текущих значений из X, Y и Z
        "mov ebx, [%[y_ptr] + r9*4]\n"
        "mov ecx, [%[z_ptr] + r10*4]\n"

        "cmp eax, ebx\n"            // Сравнение X[i] и Y[j] для выбора указателя
        "jl inc_i\n"
        "jg inc_j\n"

        "cmp eax, ecx\n"            // Сравнение X[i] с Z[k] при равенстве первых двух
        "jl inc_k\n"
        "jg inc_k\n"

        "mov %[res], eax\n"         // Сохранение результата, если X[i] == Y[j] == Z[k]
        "jmp loop_end\n"

        "inc_i:\n"                  // Инкремент указателя первого массива
        "inc r8\n"
        "jmp find_loop\n"

        "inc_j:\n"                  // Инкремент указателя второго массива
        "inc r9\n"
        "jmp find_loop\n"

        "inc_k:\n"                  // Инкремент указателя третьего массива
        "inc r10\n"
        "jmp find_loop\n"

        "not_found:\n"              // Установка -1, если совпадений не найдено
        "mov dword ptr [%[res]], -1\n"

        "loop_end:\n"               // Завершение вставки и возврат к синтаксису AT&T
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