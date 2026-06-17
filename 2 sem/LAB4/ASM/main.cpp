#include <iostream>
#include <vector>
#include "Function.h"

int main() {
    char* input = nullptr;
    char* delimiters = nullptr;
    char* extracted_string = nullptr;

    try {
        std::cout << "--- Проверка работы C++ + ASM ---" << std::endl;

        input = InputString("Введите строку: ");
        delimiters = InputDelimiters("Введите символы-разделители: ");

        extracted_string = ExtractWords(input, delimiters);

        std::vector<char*> words = SplitIntoWords(extracted_string);

        int max_unique = FindMaxUniqueCount(words);
        char* result = CreateResultString(words, max_unique);

        std::cout << "\nРезультат:" << std::endl;
        std::cout << "Слова с макс. кол-вом уникальных символов (" << max_unique << "): " << result << std::endl;

        CleanupMemory(result);
        CleanupWordVector(words);

    } catch (const StringException& e) {
        std::cerr << "\nПроизошла ошибка: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "\nНепредвиденная ошибка: " << e.what() << std::endl;
    }

    CleanupMemory(input);
    CleanupMemory(delimiters);
    CleanupMemory(extracted_string);

    return 0;
}