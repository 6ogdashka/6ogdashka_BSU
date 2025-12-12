#include "russian.h"
#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

namespace {

bool IsDelimiter(char symbol, const std::string& delimiters) {
    return delimiters.find(symbol) != std::string::npos;
}

std::vector<std::string> ExtractWords(const std::string& input_str, const std::string& delimiters) {
    std::vector<std::string> words;
    std::string current_word;
    
    for (char symbol : input_str) {
        if (IsDelimiter(symbol, delimiters)) {
            if (!current_word.empty()) {
                words.push_back(current_word);
                current_word.clear();
            }
        } else {
            current_word += symbol;
        }
    }
    
    if (!current_word.empty()) {
        words.push_back(current_word);
    }
    
    return words;
}

size_t FindMaxWordLength(const std::vector<std::string>& words) {
    if (words.empty()) {
        return 0;
    }
    
    size_t max_length = 0;
    for (const std::string& word : words) {
        if (word.length() > max_length) {
            max_length = word.length();
        }
    }
    
    return max_length;
}

std::vector<std::string> FilterWordsByLength(const std::vector<std::string>& words, size_t target_length) {
    std::vector<std::string> result;
    
    for (const std::string& word : words) {
        if (word.length() == target_length) {
            result.push_back(word);
        }
    }
    
    return result;
}

std::string JoinWords(const std::vector<std::string>& words, const std::string& separator) {
    if (words.empty()) {
        return "";
    }
    
    std::string result;
    for (size_t i = 0; i < words.size(); ++i) {
        result += words[i];
        if (i < words.size() - 1) {
            result += separator;
        }
    }
    
    return result;
}

bool IsInputEmpty(const std::string& input) {
    if (input.empty()) {
        return true;
    }
    
    for (char symbol : input) {
        if (symbol != ' ' && symbol != '\t' && symbol != '\n' && symbol != '\r') {
            return false;
        }
    }
    
    return true;
}

bool GetStringInput(const std::string& prompt, std::string& output) {
    std::cout << prompt;
    if (!std::getline(std::cin, output)) {
        std::cerr << "Ошибка ввода\n";
        return false;
    }
    return true;
}

}

int main() {
    setRussianLocale();
    
    std::string input_str;
    if (!GetStringInput("Введите строку: ", input_str)) {
        return 1;
    }
    
    if (IsInputEmpty(input_str)) {
        std::cout << "Ошибка: введена пустая строка или строка из пробельных символов\n";
        return 1;
    }
    
    std::string delimiters;
    if (!GetStringInput("Введите символы-разделители: ", delimiters)) {
        return 1;
    }
    
    std::vector<std::string> words = ExtractWords(input_str, delimiters);
    
    if (words.empty()) {
        std::cout << "В вашей строке нет ни одного слова\n";
        return 0;
    }
    
    size_t max_word_length = FindMaxWordLength(words);
    std::vector<std::string> longest_words = FilterWordsByLength(words, max_word_length);
    std::string result = JoinWords(longest_words, " ");
    
    std::cout << "Самые длинные слова в вашей строке: " << result << "\n";
    
    return 0;
}