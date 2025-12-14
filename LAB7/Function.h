#ifndef FUNCTION_H
#define FUNCTION_H

#include <cstddef>
#include <cstring>
#include <iostream>
#include <limits>
#include <unordered_map>
#include <vector>
#include <stdexcept>

class StringException : public std::runtime_error {
public:
    explicit StringException(const std::string& message);
};

class MemoryAllocationException : public StringException {
public:
    explicit MemoryAllocationException(const std::string& message);
};

class InputException : public StringException {
public:
    explicit InputException(const std::string& message);
};

const size_t kMaxSize = 300;

char* AllocateString(size_t size);
void SafeStringCopy(char* dest, const char* src, size_t dest_size);
int CountUniqueSymbols(const char* str);
bool ContainsSymbol(char symbol, const char* str);
bool IsStringEmptyOrWhitespace(const char* str);
bool IsValidDelimiterString(const char* delimiters);
char* InputString(const char* prompt);
char* InputDelimiters(const char* prompt);
char* ExtractWords(const char* input_str, const char* delimiters);
std::vector<char*> SplitIntoWords(char* words_str);
char* CopyWord(const char* word);
int FindMaxUniqueCount(const std::vector<char*>& words);
char* CreateResultString(const std::vector<char*>& words, int max_unique_count);
void CleanupMemory(char* str);
void CleanupWordVector(std::vector<char*>& words);

#endif