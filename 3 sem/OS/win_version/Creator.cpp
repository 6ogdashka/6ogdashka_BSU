#include <iostream>
#include <string>
#include <fstream>
#include "employee.h"

void Creator(const std::string& BinFileName, int n) {
    std::ofstream file(BinFileName, std::ios::binary);
    std::cout << "Введите пожалуйста данные о " << n << " сотрудниках( id, имя(не более 9 букв), и колличество часов)\n";
    for (int i = 0; i < n; i++) {
        employee buff{};
        std::cin >> buff;
        file.write(reinterpret_cast<const char*>(&buff), sizeof(buff));
    }
}

int main(int argc, char* argv[]) {
    std::string BinFileName = argv[1];
    int n = std::stoi(argv[2]);
    Creator(BinFileName, n);
    return 0;
}