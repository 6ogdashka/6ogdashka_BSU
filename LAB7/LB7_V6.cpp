#include "russian.h"
#include <cstddef>
#include <cstring>
#include <iostream>
#include <limits>
#include <unordered_map>
#include <vector>

namespace {

const size_t kMaxSize = 300;

char* AllocateString(size_t size) {
    char* str = new (std::nothrow) char[size];
    if (str == nullptr) {
        std::cerr << "Ошибка: не удалось выделить память\n";
        return nullptr;
    }
    std::memset(str, 0, size);
    return str;
}

bool SafeStringCopy(char* dest, const char* src, size_t dest_size) {
    if (dest == nullptr || src == nullptr || dest_size == 0) {
        return false;
    }
    
    size_t src_len = std::strlen(src);
    if (src_len >= dest_size) {
        std::cerr << "Предупреждение: строка обрезана при копировании\n";
        src_len = dest_size - 1;
    }
    
    std::strncpy(dest, src, src_len);
    dest[src_len] = '\0';
    return true;
}

int CountUniqueSymbols(const char* str) {
    if (str == nullptr || str[0] == '\0') {
        return 0;
    }
    
    std::unordered_map<char, int> symbol_count;
    size_t i = 0;
    
    while (str[i] != '\0') {
        ++symbol_count[str[i]];
        ++i;
    }
    
    int unique_counter = 0;
    for (const auto& pair : symbol_count) {
        if (pair.second == 1) {
            ++unique_counter;
        }
    }
    
    return unique_counter;
}

bool ContainsSymbol(char symbol, const char* str) {
    if (str == nullptr) {
        return false;
    }
    
    size_t i = 0;
    while (str[i] != '\0') {
        if (str[i] == symbol) {
            return true;
        }
        ++i;
    }
    return false;
}

bool SafeInputString(const char* prompt, char* buffer, size_t buffer_size) {
    if (buffer == nullptr || buffer_size == 0) {
        std::cerr << "Ошибка: неверный буфер для ввода\n";
        return false;
    }
    
    std::cout << prompt;
    
    if (!std::cin.getline(buffer, buffer_size)) {
        if (std::cin.gcount() == buffer_size - 1) {
            std::cerr << "Предупреждение: введенная строка была обрезана\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else if (std::cin.eof()) {
            std::cerr << "Ошибка: достигнут конец файла (EOF)\n";
            std::cin.clear();
            return false;
        } else {
            std::cerr << "Ошибка ввода\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return false;
        }
    }
    
    return true;
}

bool IsStringEmptyOrWhitespace(const char* str) {
    if (str == nullptr || str[0] == '\0') {
        return true;
    }
    
    size_t i = 0;
    while (str[i] != '\0') {
        if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && str[i] != '\r') {
            return false;
        }
        ++i;
    }
    return true;
}

char* ExtractWords(const char* input_str, const char* delimiters) {
    if (input_str == nullptr || input_str[0] == '\0') {
        return nullptr;
    }
    
    char* words = AllocateString(kMaxSize + 1);
    if (words == nullptr) {
        return nullptr;
    }
    
    size_t input_index = 0;
    size_t words_index = 0;
    bool last_was_delimiter = true;
    
    while (input_str[input_index] != '\0' && words_index < kMaxSize) {
        if (ContainsSymbol(input_str[input_index], delimiters)) {
            if (!last_was_delimiter && words_index < kMaxSize - 1) {
                words[words_index] = ' ';
                ++words_index;
                last_was_delimiter = true;
            }
        } else {
            words[words_index] = input_str[input_index];
            ++words_index;
            last_was_delimiter = false;
        }
        ++input_index;
    }
    
    if (words_index > 0 && words[words_index - 1] == ' ') {
        words[words_index - 1] = '\0';
    } else {
        words[words_index] = '\0';
    }
    
    return words;
}

std::vector<char*> SplitIntoWords(char* words_str) {
    std::vector<char*> words;
    
    if (words_str == nullptr || words_str[0] == '\0') {
        return words;
    }
    
    size_t i = 0;
    size_t word_start = 0;
    bool in_word = false;
    
    while (words_str[i] != '\0') {
        if (words_str[i] == ' ') {
            if (in_word) {
                words_str[i] = '\0';
                words.push_back(words_str + word_start);
                in_word = false;
            }
        } else {
            if (!in_word) {
                word_start = i;
                in_word = true;
            }
        }
        ++i;
    }
    
    if (in_word) {
        words.push_back(words_str + word_start);
    }
    
    return words;
}

char* CopyWord(const char* word) {
    if (word == nullptr) {
        return nullptr;
    }
    
    size_t len = std::strlen(word);
    char* copy = AllocateString(len + 1);
    if (copy == nullptr) {
        return nullptr;
    }
    
    SafeStringCopy(copy, word, len + 1);
    return copy;
}

int FindMaxUniqueCount(const std::vector<char*>& words) {
    if (words.empty()) {
        return 0;
    }
    
    int max_unique = 0;
    
    for (const char* word : words) {
        if (word != nullptr) {
            int unique_count = CountUniqueSymbols(word);
            if (unique_count > max_unique) {
                max_unique = unique_count;
            }
        }
    }
    
    return max_unique;
}

void PrintWordsWithMaxUnique(const std::vector<char*>& words, int max_unique) {
    if (words.empty()) {
        std::cout << "Нет слов для вывода\n";
        return;
    }
    
    std::cout << "Слова с максимальным количеством уникальных символов (" 
              << max_unique << "):\n";
    
    bool found = false;
    for (const char* word : words) {
        if (word != nullptr && CountUniqueSymbols(word) == max_unique) {
            std::cout << word << "\n";
            found = true;
        }
    }
    
    if (!found) {
        std::cout << "Не найдено слов с " << max_unique << " уникальными символами\n";
    }
}

void FreeStringVector(std::vector<char*>& string_vector) {
    for (char* str : string_vector) {
        delete[] str;
    }
    string_vector.clear();
}

}

int main() {
    setRussianLocale();
    
    char* input_str = AllocateString(kMaxSize + 1);
    char* delimiters = AllocateString(kMaxSize + 1);
    
    if (input_str == nullptr || delimiters == nullptr) {
        delete[] input_str;
        delete[] delimiters;
        return 1;
    }
    
    if (!SafeInputString("Введите строку: ", input_str, kMaxSize + 1)) {
        delete[] input_str;
        delete[] delimiters;
        return 1;
    }
    
    if (IsStringEmptyOrWhitespace(input_str)) {
        std::cout << "Ошибка: введена пустая строка или строка из пробельных символов\n";
        delete[] input_str;
        delete[] delimiters;
        return 1;
    }
    
    if (!SafeInputString("Введите символы-разделители: ", delimiters, kMaxSize + 1)) {
        delete[] input_str;
        delete[] delimiters;
        return 1;
    }
    
    char* words_str = ExtractWords(input_str, delimiters);
    if (words_str == nullptr || words_str[0] == '\0') {
        std::cout << "Слова не найдены\n";
        delete[] input_str;
        delete[] delimiters;
        delete[] words_str;
        return 0;
    }
    
    std::vector<char*> words = SplitIntoWords(words_str);
    
    if (words.empty()) {
        std::cout << "Слова не найдены\n";
        delete[] input_str;
        delete[] delimiters;
        delete[] words_str;
        return 0;
    }
    
    std::vector<char*> word_copies;
    for (char* word : words) {
        char* copy = CopyWord(word);
        if (copy != nullptr) {
            word_copies.push_back(copy);
        }
    }
    
    if (word_copies.empty()) {
        std::cout << "Не удалось обработать слова\n";
        delete[] input_str;
        delete[] delimiters;
        delete[] words_str;
        return 1;
    }
    
    int max_unique = FindMaxUniqueCount(word_copies);
    
    PrintWordsWithMaxUnique(word_copies, max_unique);
    
    delete[] input_str;
    delete[] delimiters;
    delete[] words_str;
    FreeStringVector(word_copies);
    
    return 0;
}