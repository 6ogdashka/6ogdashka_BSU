#include "Library.cpp"
#include <iostream>
#include "russian.h"

int main () {
    setRussianLocale();
    Library L;
    Book book(12345, "Программирование на C++", 
            {{"Иван", "Иванович", "Иванов"}, {"Петр", "Петрович", "Петров"}}, 
            {2023});
            
    std::cout << book << std::endl;
    L.Add(book);
    L.Add(book);
    auto it = L.FindBookByName("Программирование на C++");
    Book d = (*it);
    std::cout << d << '\n';
    L.EraseBookByName("Программирование на C++");
    auto new_it = L.FindBookByName("Программирование на C++");
    if ( new_it == L.end()) {
        std::cout << -1;
    }
    return 0;
}