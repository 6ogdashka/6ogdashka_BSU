#include "russian.h"
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

class StringProcessorException : public std::runtime_error {
public:
    explicit StringProcessorException(const std::string& message) 
        : std::runtime_error(message) {}
};

class InputException : public StringProcessorException {
public:
    explicit InputException(const std::string& message) 
        : StringProcessorException("Ошибка ввода: " + message) {}
};

class EmptyInputException : public InputException {
public:
    explicit EmptyInputException(const std::string& message) 
        : InputException("Пустой ввод: " + message) {}
};

class NoWordsException : public StringProcessorException {
public:
    explicit NoWordsException(const std::string& message) 
        : StringProcessorException("Нет слов: " + message) {}
};

struct ProcessingResult {
    std::vector<std::string> words;
    std::vector<std::string> longest_words;
    size_t total_words_count;
    size_t max_word_length;
    size_t longest_words_count;
    std::string result_string;
};

std::string InputString(const std::string& prompt) {
    std::cout << prompt;
    
    std::string input;
    if (!std::getline(std::cin, input)) {
        if (std::cin.eof()) {
            throw InputException("Обнаружен конец файла (EOF)");
        } else {
            throw InputException("Ошибка чтения строки");
        }
    }
    
    for (char symbol : input) {
        if (symbol != ' ' && symbol != '\t' && symbol != '\n' && symbol != '\r') {
            return input;
        }
    }
    
    throw EmptyInputException("Строка не должна быть пустой или состоять только из пробельных символов");
}

std::string InputDelimiters(const std::string& prompt) {
    std::string delimiters = InputString(prompt);
    
    if (delimiters.empty()) {
        throw EmptyInputException("Строка разделителей не должна быть пустой");
    }
    
    return delimiters;
}

bool IsDelimiter(char symbol, const std::string& delimiters) {
    return delimiters.find(symbol) != std::string::npos;
}

std::vector<std::string> ExtractWords(const std::string& input_str, const std::string& delimiters) {
    if (input_str.empty()) {
        throw StringProcessorException("Исходная строка пуста");
    }
    
    if (delimiters.empty()) {
        throw StringProcessorException("Некорректная строка разделителей");
    }
    
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
    
    if (words.empty()) {
        throw NoWordsException("В строке не найдено слов");
    }
    
    return words;
}

size_t FindMaxWordLength(const std::vector<std::string>& words) {
    if (words.empty()) {
        throw NoWordsException("Список слов пуст");
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
    
    if (result.empty()) {
        throw StringProcessorException("Не найдено слов заданной длины");
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

void PrintInputData(const std::string& input_str, const std::string& delimiters) {
    std::cout << "Введенная строка: \"" << input_str << "\"\n\n";
    std::cout << "Разделители: \"" << delimiters << "\"\n\n";
}

void PrintProcessingInfo(size_t word_count, size_t max_length, size_t longest_count) {
    std::cout << "Найдено слов: " << word_count << "\n";
    std::cout << "Максимальная длина слова: " << max_length << "\n";
    std::cout << "Найдено самых длинных слов: " << longest_count << "\n";
}

void PrintResult(const std::string& result) {
    std::cout << "\n=== РЕЗУЛЬТАТ ===\n";
    std::cout << "Самые длинные слова: " << result << "\n";
}

ProcessingResult ProcessInput(const std::string& input_str, const std::string& delimiters) {
    std::vector<std::string> words = ExtractWords(input_str, delimiters);
    size_t max_word_length = FindMaxWordLength(words);
    std::vector<std::string> longest_words = FilterWordsByLength(words, max_word_length);
    std::string result_string = JoinWords(longest_words, " ");
    
    return {words, longest_words, words.size(), max_word_length, longest_words.size(), result_string};
}

void PrintSuccessMessage() {
    std::cout << "\nПрограмма завершена успешно.\n";
}

void PrintErrorMessage(const std::exception& e, const std::string& error_type) {
    std::cerr << "\n=== " << error_type << " ===\n";
    std::cerr << e.what() << "\n";
}

int RunProgram() {
    setRussianLocale();
    
    std::cout << "=== ПРОГРАММА ДЛЯ ПОИСКА САМЫХ ДЛИННЫХ СЛОВ ===\n\n";
    
    std::string input_str = InputString("Введите строку: ");
    std::string delimiters = InputDelimiters("Введите символы-разделители: ");
    
    PrintInputData(input_str, delimiters);
    
    ProcessingResult result = ProcessInput(input_str, delimiters);
    PrintProcessingInfo(result.total_words_count, result.max_word_length, result.longest_words_count);
    
    PrintResult(result.result_string);
    PrintSuccessMessage();
    
    return 0;
}

int main() {
    try {
        return RunProgram();
        
    } catch (const EmptyInputException& e) {
        PrintErrorMessage(e, "ОШИБКА ВВОДА");
        return 1;
        
    } catch (const NoWordsException& e) {
        PrintErrorMessage(e, "ОШИБКА ОБРАБОТКИ");
        return 1;
        
    } catch (const StringProcessorException& e) {
        PrintErrorMessage(e, "ОШИБКА");
        return 1;
        
    } catch (const std::exception& e) {
        PrintErrorMessage(e, "НЕИЗВЕСТНАЯ ОШИБКА");
        return 1;
    }
}