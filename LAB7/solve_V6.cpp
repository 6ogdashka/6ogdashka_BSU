#include <cstddef>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include "russian.h"

const size_t MAX_SIZE = 300;

int countingUnique( char* string, size_t size);

int countingUnique( char* string, size_t size) {
    std::unordered_map<char, int> unique;
    int unique_counter{};
    for ( int i {}; i < size; ++i ) {
        ++unique[string[i]];
        {
            if ( unique[string[i]] == 1) {
                ++unique_counter;
            }
        }
    }
    return unique_counter;
}

bool FindSymbol( char symbol, char* string) {
    size_t i {};
    while ( string[i] != '\0') {
        if ( string[i] == symbol) {
            return true;
        }
        ++i;
    }
    return false;
}

int main () {
    setRussianLocale();
    char* input_str = new char[MAX_SIZE+1]();
    std::cout << "Введите строку: ";
    std::cin.getline(input_str,MAX_SIZE);

    char* delimiters = new char[MAX_SIZE+1]();
    std::cout << "Введите символы-разделители: ";
    std::cin.getline(delimiters,MAX_SIZE);

    size_t i {};
    while ( input_str[i] != '\0') {
        if ( FindSymbol(input_str[i], delimiters) ) {

        } else {

        }
    }

}