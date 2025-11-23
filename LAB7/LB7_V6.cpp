#include "russian.h"
#include <cstddef>
#include <cstring>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <unordered_map>

const size_t MAX_SIZE = 300; 

int countingUnique(char* string) {
    std::unordered_map<char, int> unique;
    int unique_counter{};
    size_t i = 0;
    while (string[i] != '\0') {
        ++unique[string[i]];
        ++i;
    }
    i = 0;
    while (string[i] != '\0') {
        if (unique[string[i]] == 1) {
            ++unique_counter;
        }
        ++i;
    }
    return unique_counter;
}

bool FindSymbol(char symbol, char* string) {
    size_t i{};
    while (string[i] != '\0') {
        if (string[i] == symbol) {
            return true;
        }
        ++i;
    }
    return false;
}

int main() {
    setRussianLocale();
    char* input_str = new char[MAX_SIZE + 1]();
    std::cout << "Введите строку: ";
    std::cin.getline(input_str, MAX_SIZE);

    char* delimiters = new char[MAX_SIZE + 1]();
    std::cout << "Введите символы-разделители: ";
    std::cin.getline(delimiters, MAX_SIZE);

    size_t i{};
    size_t j{};
    bool word_exist = false;
    char* words = new char[MAX_SIZE + 1]();
    while (input_str[i] != '\0') {
        if (FindSymbol(input_str[i], delimiters)) {
            if (j > 0 && words[j - 1] != ' ') {
                words[j] = ' ';
                j++;
            }
        } else {
            word_exist = true;
            words[j] = input_str[i];
            j++;
        }
        ++i;
    }
    words[j] = '\0';

    if (word_exist == false) {
        std::cout << "Слова не найдены\n";
        delete[] input_str;
        delete[] delimiters;
        delete[] words;
        return 0;
    }

    int max_unique = 0;
    size_t start = 0;

    for (size_t pos = 0; pos <= j; pos++) {  // j это длина массива words из прошлого массива
        if (words[pos] == ' ' || words[pos] == '\0') {
            if (pos > start) {
                char* word = new char[MAX_SIZE]();
                strncpy(word, words + start, pos - start);
                word[pos - start] = '\0';

                int unique_count = countingUnique(word);
                if (unique_count > max_unique) { // находим максимальное колво уникальных символов в слове
                    max_unique = unique_count;
                }
                delete[] word;
            }
            start = pos + 1;
        }
    }

    start = 0;

    for (size_t pos = 0; pos <= j; pos++) {
        if (words[pos] == ' ' || words[pos] == '\0') {
            if (pos > start) {
                char* word = new char[MAX_SIZE]();
                strncpy(word, words + start, pos - start);
                word[pos - start] = '\0';

                if (countingUnique(word) == max_unique) {  // находим все слова в которых колво уникальных символов равно максимальному и выводим
                    std::cout << word << "\n";
                }
                delete[] word;
            }
            start = pos + 1;
        }
    }

    delete[] input_str;
    delete[] delimiters;
    delete[] words;

    return 0;
}