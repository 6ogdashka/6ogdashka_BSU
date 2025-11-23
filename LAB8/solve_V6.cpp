#include <cstddef>
#include <iostream>
#include <string>
#include <vector>
#include "russian.h"

//я решил не разбивать на функции, потому что это код в раза 2 больше сделает.ф

int main () {
    setRussianLocale();
    std::string input_str;
    std::cout << "Введите строку: ";
    std::getline(std::cin, input_str);

    std::string delimiters;
    std::cout << "Введите символы-разделители: ";
    std::getline(std::cin, delimiters);

    std::vector<std::string> words;
    std::string current_word;
    size_t max_word_size {};
    bool word_exist = false;

    for ( char symbol : input_str) {
        if (delimiters.find(symbol) != std::string::npos) {
            if (!current_word.empty()) {
                if ( current_word.size() > max_word_size ) {
                    max_word_size = static_cast<size_t>(current_word.size());
                }
            }
            words.push_back(current_word);
            current_word.clear();
        } else {
            word_exist = true;
            current_word += symbol;
        }
    }
    std::string result{};
    if ( word_exist != false) {
    for ( std::string str : words) {
        if ( str.size() == max_word_size) {
            result += str;
            result += " ";
        }
    }
    std::cout << "Самые длинные слова в вашей строке: " << result;
    return 0;   
    } else {
        std::cout << "В вашей строке нет ни одного слова ";
        return 0;
    }
}