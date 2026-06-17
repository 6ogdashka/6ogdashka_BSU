#include <iostream>

extern "C" {
    int asm_compare(const char* s1, const char* s2);
    void asm_copy(char* dest, const char* src);
    void asm_replace(char* str, char old_char, char new_char);
}

int main() {
    const char* s1 = "Apple";
    const char* s2 = "Apple";
    const char* s3 = "Apply";
    
    std::cout << "1. asm_compare:" << std::endl;
    std::cout << s1 << " == " << s2 << ": " << (asm_compare(s1, s2) == 0) << std::endl;
    std::cout << s1 << " == " << s3 << ": " << (asm_compare(s1, s3) == 0) << std::endl;

    const char* original = "Bogdan";
    char buffer[64];
    
    std::cout << "\n2. asm_copy:" << std::endl;
    asm_copy(buffer, original);
    std::cout << "Result: " << buffer << std::endl;

    char text[] = "abracadabra";
    
    std::cout << "\n3. asm_replace:" << std::endl;
    std::cout << "Before: " << text << std::endl;
    asm_replace(text, 'a', 'O');
    std::cout << "After:  " << text << std::endl;

    return 0;
}