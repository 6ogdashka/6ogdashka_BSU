#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <stdexcept>
#include "russian.h"

namespace {

const int kMaxOutputLines = 10;

int ExpandAroundCenter(const std::string& s, int left, int right) {
    while (left >= 0 && right < static_cast<int>(s.length()) && 
           s[left] == s[right]) {
        left--;
        right++;
    }
    return right - left - 1;
}

int MaxPalindromeLength(const std::string& str) {
    if (str.empty()) {
        return 0;
    }

    int max_len = 0;

    for (int i = 0; i < static_cast<int>(str.length()); i++) {
        int len1 = ExpandAroundCenter(str, i, i);
        int len2 = ExpandAroundCenter(str, i, i + 1);

        if (len1 > max_len) max_len = len1;
        if (len2 > max_len) max_len = len2;
    }

    return max_len;
}

void CheckInputFile(std::ifstream& fin) {
    if (!fin.is_open()) {
        throw std::runtime_error("Не удалось открыть входной файл");
    }
    
    if (!fin.good()) {
        throw std::runtime_error("Входной файл поврежден или недоступен");
    }
    
    fin.seekg(0, std::ios::end);
    if (fin.tellg() == 0) {
        throw std::runtime_error("Входной файл пуст");
    }
    fin.seekg(0, std::ios::beg);
}

void CheckOutputFile(std::ofstream& fout) {
    if (!fout.is_open()) {
        throw std::runtime_error("Не удалось открыть выходной файл");
    }
    
    if (!fout.good()) {
        throw std::runtime_error("Выходной файл недоступен для записи");
    }
}

std::vector<std::string> ReadWordsFromFile(const std::string& filename) {
    std::ifstream file(filename);
    CheckInputFile(file);
    
    std::vector<std::string> words;
    std::string current_str;
    
    while (std::getline(file, current_str)) {
        words.push_back(current_str);
    }
    
    file.close();
    
    if (words.empty()) {
        throw std::runtime_error("Файл не содержит слов для обработки");
    }
    
    return words;
}

std::unordered_map<std::string, int> CalculatePalindromeLengths(const std::vector<std::string>& words) {
    std::unordered_map<std::string, int> palindrome_lengths;
    
    for (const std::string& word : words) {
        palindrome_lengths[word] = MaxPalindromeLength(word);
    }
    
    return palindrome_lengths;
}

int FindMaxPalindromeLength(const std::unordered_map<std::string, int>& palindrome_lengths) {
    if (palindrome_lengths.empty()) {
        throw std::runtime_error("Не удалось вычислить длины палиндромов");
    }
    
    int max_length = 0;
    for (const auto& [word, length] : palindrome_lengths) {
        if (length > max_length) {
            max_length = length;
        }
    }
    
    return max_length;
}

void WriteResultsToFile(const std::string& filename,
                       const std::vector<std::string>& words,
                       const std::unordered_map<std::string, int>& palindrome_lengths,
                       int max_palindrome_length) {
    std::ofstream ofile(filename);
    CheckOutputFile(ofile);
    
    int counter = 0;
    for (size_t i = 0; i < words.size(); ++i) {
        if (palindrome_lengths.at(words[i]) == max_palindrome_length && counter < kMaxOutputLines) {
            ofile << words[i] << '\n';
            ++counter;
        }
    }
    
    ofile.close();
    
    if (counter == 0) {
        throw std::runtime_error("Не найдено слов с максимальной длиной палиндрома");
    }
}

void ProcessFile(const std::string& input_filename, const std::string& output_filename) {
    std::vector<std::string> words = ReadWordsFromFile(input_filename);
    std::unordered_map<std::string, int> palindrome_lengths = CalculatePalindromeLengths(words);
    int max_palindrome_length = FindMaxPalindromeLength(palindrome_lengths);
    WriteResultsToFile(output_filename, words, palindrome_lengths, max_palindrome_length);
    
    std::cout << "Обработка завершена успешно. Результаты записаны в " << output_filename << std::endl;
}

}

int main() {
    setRussianLocale();
    try {
        const std::string input_filename = "input.txt";
        const std::string output_filename = "output.txt";
        
        ProcessFile(input_filename, output_filename);
        return 0;
        
    } catch (const std::runtime_error& e) {
        std::cerr << "Ошибка выполнения: " << e.what() << std::endl;
        return 1;
        
    } catch (const std::exception& e) {
        std::cerr << "Стандартная ошибка: " << e.what() << std::endl;
        return 1;
        
    } catch (...) {
        std::cerr << "Неизвестная ошибка!" << std::endl;
        return 1;
    }
}