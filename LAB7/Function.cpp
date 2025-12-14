#include "Function.h"
#include "russian.h"

StringException::StringException(const std::string& message) 
    : std::runtime_error(message) {}

MemoryAllocationException::MemoryAllocationException(const std::string& message) 
    : StringException("Ошибка выделения памяти: " + message) {}

InputException::InputException(const std::string& message) 
    : StringException("Ошибка ввода: " + message) {}

char* AllocateString(size_t size) {
    char* str = new (std::nothrow) char[size];
    if (str == nullptr) {
        throw MemoryAllocationException("Не удалось выделить " + 
                                      std::to_string(size) + " байт");
    }
    std::memset(str, 0, size);
    return str;
}

void SafeStringCopy(char* dest, const char* src, size_t dest_size) {
    if (dest == nullptr || src == nullptr || dest_size == 0) {
        throw StringException("Некорректные параметры для копирования строки");
    }
    
    size_t src_len = std::strlen(src);
    if (src_len >= dest_size) {
        throw StringException("Строка слишком длинная для буфера");
    }
    
    std::strncpy(dest, src, src_len);
    dest[src_len] = '\0';
}

int CountUniqueSymbols(const char* str) {
    if (str == nullptr) {
        return 0;
    }
    
    if (str[0] == '\0') {
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

bool IsStringEmptyOrWhitespace(const char* str) {
    if (str == nullptr) {
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

bool IsValidDelimiterString(const char* delimiters) {
    if (delimiters == nullptr) {
        return false;
    }
    
    if (delimiters[0] == '\0') {
        return false;
    }
    
    return true;
}

char* InputString(const char* msg) {
    std::cout << msg;
    
    char* buffer = AllocateString(kMaxSize + 1);
    
    try {
        if (!std::cin.getline(buffer, kMaxSize)) {
            if (std::cin.gcount() == kMaxSize) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                CleanupMemory(buffer);
                throw InputException("Строка слишком длинная (максимум " + 
                                   std::to_string(kMaxSize) + " символов)");
            } else {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                CleanupMemory(buffer);
                throw InputException("Ошибка чтения строки");
            }
        }
        
        if (IsStringEmptyOrWhitespace(buffer)) {
            CleanupMemory(buffer);
            throw InputException("Строка не должна быть пустой или состоять только из пробельных символов");
        }
        
        return buffer;
        
    } catch (...) {
        CleanupMemory(buffer);
        throw;
    }
}

char* InputDelimiters(const char* msg) {
    char* delimiters = InputString(msg);
    
    if (!IsValidDelimiterString(delimiters)) {
        CleanupMemory(delimiters);
        throw InputException("Строка разделителей не должна быть пустой");
    }
    
    return delimiters;
}

char* ExtractWords(const char* input_str, const char* delimiters) {
    if (input_str == nullptr || input_str[0] == '\0') {
        throw StringException("Исходная строка пуста");
    }
    
    if (!IsValidDelimiterString(delimiters)) {
        throw StringException("Некорректная строка разделителей");
    }
    
    char* words = AllocateString(kMaxSize + 1);
    
    try {
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
        
        if (words[0] == '\0') {
            CleanupMemory(words);
            throw StringException("В строке не найдено слов");
        }
        
        return words;
        
    } catch (...) {
        CleanupMemory(words);
        throw;
    }
}

std::vector<char*> SplitIntoWords(char* words_str) {
    std::vector<char*> words;
    
    if (words_str == nullptr || words_str[0] == '\0') {
        return words;
    }
    
    size_t i = 0;
    size_t word_start = 0;
    bool in_word = false;
    
    try {
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
        
        if (words.empty()) {
            throw StringException("Не удалось извлечь слова из строки");
        }
        
        return words;
        
    } catch (...) {
        words.clear();
        throw;
    }
}

char* CopyWord(const char* word) {
    if (word == nullptr) {
        throw StringException("Попытка копирования нулевого указателя");
    }
    
    size_t len = std::strlen(word);
    char* copy = AllocateString(len + 1);
    SafeStringCopy(copy, word, len + 1);
    return copy;
}

int FindMaxUniqueCount(const std::vector<char*>& words) {
    if (words.empty()) {
        throw StringException("Список слов пуст");
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
    
    if (max_unique == 0) {
        throw StringException("Не удалось определить уникальные символы в словах");
    }
    
    return max_unique;
}

char* CreateResultString(const std::vector<char*>& words, int max_unique_count) {
    if (words.empty()) {
        throw StringException("Список слов пуст");
    }
    
    size_t total_length = 0;
    size_t word_count = 0;
    
    for (const char* word : words) {
        if (word != nullptr && CountUniqueSymbols(word) == max_unique_count) {
            total_length += std::strlen(word);
            ++word_count;
        }
    }
    
    if (word_count == 0) {
        throw StringException("Не найдено слов с максимальным количеством уникальных символов");
    }
    
    total_length += (word_count - 1) * 2;
    
    char* result = AllocateString(total_length + 1);
    
    try {
        size_t current_pos = 0;
        bool first_word = true;
        
        for (const char* word : words) {
            if (word != nullptr && CountUniqueSymbols(word) == max_unique_count) {
                if (!first_word) {
                    result[current_pos++] = ',';
                    result[current_pos++] = ' ';
                }
                
                size_t word_len = std::strlen(word);
                std::strncpy(result + current_pos, word, word_len);
                current_pos += word_len;
                first_word = false;
            }
        }
        
        result[current_pos] = '\0';
        return result;
        
    } catch (...) {
        CleanupMemory(result);
        throw;
    }
}

void CleanupMemory(char* str) {
    if (str != nullptr) {
        delete[] str;
    }
}

void CleanupWordVector(std::vector<char*>& words) {
    for (char* word : words) {
        CleanupMemory(word);
    }
    words.clear();
}