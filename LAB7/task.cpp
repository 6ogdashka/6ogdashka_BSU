#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <unordered_map>

size_t countUniqueChars(const std::string& word) {
    const size_t size = word.length();
    size_t unique_count = 0;
    std::unordered_map<char, int> counter {};
    for ( size_t i{0}; i < size; ++i) {
        ++counter[word[i]];
    }
    for ( size_t i {0}; i < size; ++i) {
        if ( counter[word[i]] == 1) {
            ++unique_count;
        }
     }
    return unique_count;
}

std::string processString(const std::string& input) {
    std::vector<std::string> result_words;
    std::string current_word;
    size_t max_unique_count = 0;

    for (size_t i = 0; i <= input.length(); ++i) {
        if (i < input.length() && std::isalnum(static_cast<unsigned char>(input[i]))) {
            current_word += input[i];
        } 
        else if (!current_word.empty()) {
            size_t unique_count = countUniqueChars(current_word);
            
            if (unique_count > max_unique_count) {
                max_unique_count = unique_count;
                result_words.clear();
                result_words.push_back(current_word);
            } 
            else if (unique_count == max_unique_count) {
                if (std::find(result_words.begin(), result_words.end(), current_word) == result_words.end()) {
                    result_words.push_back(current_word);
                }
            }
            
            current_word.clear();
        }
    }
    if (result_words.empty()) {
        return "";
    }
    
    std::string result;
    for (size_t i = 0; i < result_words.size(); ++i) {
        if (i > 0) {
            result += ", ";
        }
        result += result_words[i];
    }
    
    return result;
}
std::string getInputString() {
    std::string input;
    std::cout << "Введите строку для анализа: ";
    std::getline(std::cin, input);
    return input;
}
void printResult(const std::string& result) {
    if (result.empty()) {
        std::cout << "В строке не найдено слов." << std::endl;
    } else {
        std::cout << "Слова с максимальным количеством различных символов: " << result << std::endl;
    }
}

int main() {
    std::string input = getInputString();
    std::string result = processString(input);
    printResult(result);
    
    return 0;
}