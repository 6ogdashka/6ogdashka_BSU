#include "Function.cpp"

int main() {
    setRussianLocale();
    
    char* input_str = nullptr;
    char* delimiters = nullptr;
    char* words_str = nullptr;
    char* result_str = nullptr;
    std::vector<char*> words;
    std::vector<char*> word_copies;
    
    try {
        std::cout << "=== ПРОГРАММА ДЛЯ ПОИСКА СЛОВ С МАКСИМАЛЬНЫМ КОЛИЧЕСТВОМ УНИКАЛЬНЫХ СИМВОЛОВ ===\n\n";
        
        input_str = InputString("Введите строку: ");
        
        delimiters = InputDelimiters("Введите символы-разделители: ");
        
        words_str = ExtractWords(input_str, delimiters);
        std::cout << "Извлеченные слова: \"" << words_str << "\"\n\n";
        
        words = SplitIntoWords(words_str);
        std::cout << "Найдено слов: " << words.size() << "\n";
        
        for (char* word : words) {
            char* copy = CopyWord(word);
            word_copies.push_back(copy);
        }
        
        int max_unique_count = FindMaxUniqueCount(word_copies);
        std::cout << "Максимальное количество уникальных символов в слове: " 
                  << max_unique_count << "\n\n";
        
        result_str = CreateResultString(word_copies, max_unique_count);
        
        std::cout << "Слова с максимальным количеством уникальных символов (" 
                  << max_unique_count << "):\n";
        std::cout << result_str << "\n";
        
        CleanupMemory(input_str);
        CleanupMemory(delimiters);
        CleanupMemory(words_str);
        CleanupMemory(result_str);
        CleanupWordVector(word_copies);
        
        std::cout << "\nПрограмма завершена успешно.\n";
        return 0;
        
    } catch (const StringException& e) {
        std::cerr << "\n=== ОШИБКА ===\n";
        std::cerr << e.what() << "\n";
        
        CleanupMemory(input_str);
        CleanupMemory(delimiters);
        CleanupMemory(words_str);
        CleanupMemory(result_str);
        CleanupWordVector(word_copies);
        
        return 1;
        
    } catch (const std::exception& e) {
        std::cerr << "\n=== НЕИЗВЕСТНАЯ ОШИБКА ===\n";
        std::cerr << e.what() << "\n";
        
        CleanupMemory(input_str);
        CleanupMemory(delimiters);
        CleanupMemory(words_str);
        CleanupMemory(result_str);
        CleanupWordVector(word_copies);
        
        return 1;
    }
}