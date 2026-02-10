#include "Library.h"

int main () {
    Library lib;
    try {
        lib.LoadFromFile("Books.txt");
        //std::cout << "Загружено книг: " << lib.GetBookCount() << std::endl;
        //std::cout << lib << std::endl;
        lib.SaveToFile("Library.txt");
        std::cout << "Успешно загружено и сохранено." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}