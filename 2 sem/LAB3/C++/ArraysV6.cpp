#include <iostream>


int main() {

    int* A = new int[5];
    int* B = new int[4];

    int sizeA, sizeB;
    std::cout << "Введите реальный размер массива A: ";
    std::cin >> sizeA;
    std::cout << "Введите реальный размер массива B: ";
    std::cin >> sizeB;

    delete[] A;
    delete[] B;

    A = new int[sizeA];
    B = new int[sizeB];

    std::cout << "Введите элементы массива A:";
    for (int i = 0; i < sizeA; ++i) {
        std::cin >> *(A + i);
    }

    std::cout << "Введите элементы массива B:";
    for (int i = 0; i < sizeB; ++i) {
        std::cin >> *(B + i);
    }

    int maxVal = *A;
    int maxArray = 1;
    int maxIndex = 0;

    for (int i = 0; i < sizeA; ++i) {
        if (*(A + i) > maxVal) {
            maxVal = *(A + i);
            maxArray = 1;
            maxIndex = i;
        }
    }
    for (int i = 0; i < sizeB; ++i) {
        if (*(B + i) > maxVal) {
            maxVal = *(B + i);
            maxArray = 2;
            maxIndex = i;
        }
    }

    if (maxArray == 1) {
        std::cout << "Массив A: ";
        for (int i = 0; i < sizeA; ++i) {
            std::cout << *(A + i) << " ";
        }
        std::cout << "\nМассив B: ";
        for (int i = 0; i < sizeB; ++i) {
            std::cout << *(B + i) << " ";
        }
    } else {
        std::cout << "Массив B: ";
        for (int i = 0; i < sizeB; ++i) {
            std::cout << *(B + i) << " ";
        }
        std::cout << "\nМассив A: ";
        for (int i = 0; i < sizeA; ++i) {
            std::cout << *(A + i) << " ";
        }
    }

    std::cout << "\nНаибольшее значение: " << maxVal << "\n";
    std::cout << "Порядковый номер в массиве "
              << (maxArray == 1 ? "A" : "B") << ": " << (maxIndex + 1) << std::endl;

    delete[] A;
    delete[] B;

    return 0;
}