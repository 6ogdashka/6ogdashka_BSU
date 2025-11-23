#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <string>
#include "russian.h"

using namespace std;

template<typename T> T** Matrix;
int rows, cols;

template<typename T> T** createMatrix(int rows, int cols);
template<typename T> void deleteMatrix(T** matrix, int rows);
template<typename T> void printMatrix(T** matrix, int rows, int cols);
template<typename T> void writeMatrixToFile(T** matrix, int rows, int cols, const string& filename);
template<typename T> void readMatrixFromFile(T** matrix, int& rows, int& cols, const string& filename);
template<typename T> T generateRandomValue();
template<> int generateRandomValue<int>();
template<> double generateRandomValue<double>();
template<> char generateRandomValue<char>();
void getMatrixSize(int& rows, int& cols, bool fromFile = false, const string& filename = "");
template<typename T> T** manualInputToFile();
template<typename T> T** randomGenerateToFile();
template<typename T> T** fileInputToConsole();
template<typename T> void search_max_minimal_el_in_matrix(T** matrix, int rows, int cols);

int main() {
    setRussianLocale();
    
    int choice, dataType;
    
    cout << "=== ПРОГРАММА ДЛЯ РАБОТЫ С МАТРИЦАМИ ===" << endl;
    cout << endl;
    cout << "Выберите способ ввода матрицы:" << endl;
    cout << "1 - Ручной ввод" << endl;
    cout << "2 - Случайная генерация" << endl;
    cout << "3 - Чтение из файла" << endl;
    cout << "Ваш выбор: ";
    cin >> choice;
    
    cout << endl;
    cout << "Выберите тип данных матрицы:" << endl;
    cout << "1 - Целые числа (int)" << endl;
    cout << "2 - Вещественные числа (double)" << endl;
    cout << "3 - Символы (char)" << endl;
    cout << "Ваш выбор: ";
    cin >> dataType;
    
    cout << endl;
    
    switch (choice) {
        case 1: {
            if (dataType == 1) {
                Matrix<int> = manualInputToFile<int>();
            } else if (dataType == 2) {
                Matrix<double> = manualInputToFile<double>();
            } else if (dataType == 3) {
                Matrix<char> = manualInputToFile<char>();
            } else { 
                cout << "Ошибка: неверный тип данных!" << endl;
                return 0;
            }
            break;
        }
        case 2: {
            if (dataType == 1) {
                Matrix<int> = randomGenerateToFile<int>();
            } else if (dataType == 2) {
                Matrix<double> = randomGenerateToFile<double>();
            } else if (dataType == 3) {
                Matrix<char> = randomGenerateToFile<char>();
            } else { 
                cout << "Ошибка: неверный тип данных!" << endl;
                return 0;
            }
            break;
        }
        case 3: {
            if (dataType == 1) {
                Matrix<int> = fileInputToConsole<int>();
            } else if (dataType == 2) {
                Matrix<double> = fileInputToConsole<double>();
            } else if (dataType == 3) {
                Matrix<char> = fileInputToConsole<char>();
            } else { 
                cout << "Ошибка: неверный тип данных!" << endl;
                return 0;
            }
            break;
        }
        default: {
            cout << "Ошибка: неверный способ ввода!" << endl;
            return 0;
        }
    }
    
    cout << endl;
    cout << "=== ПОИСК МАКСИМАЛЬНОГО ЛОКАЛЬНОГО МИНИМУМА ===" << endl;
    
    if (dataType == 1) {
        search_max_minimal_el_in_matrix(Matrix<int>, rows, cols);
    } else if (dataType == 2) {
        search_max_minimal_el_in_matrix(Matrix<double>, rows, cols);
    } else if (dataType == 3) {
        search_max_minimal_el_in_matrix(Matrix<char>, rows, cols);
    }
    cin.ignore();
    cin.get();
    return 0;
}

template<typename T>
T** createMatrix(int rows, int cols) {
    T** matrix = new T*[rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new T[cols]();
    }
    return matrix;
}

template<typename T>
void deleteMatrix(T** matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

template<typename T>
void printMatrix(T** matrix, int rows, int cols) {
    cout << "Матрица " << rows << "x" << cols << ":" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

template<typename T>
void writeMatrixToFile(T** matrix, int rows, int cols, const string& filename) {
    ofstream file(filename);
    file << rows << " " << cols << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            file << matrix[i][j] << " ";
        }
        file << endl;
    }
    cout << "Матрица успешно записана в файл: " << filename << endl;
}

template<typename T>
void readMatrixFromFile(T** matrix, int& rows, int& cols, const string& filename) {
    ifstream file(filename);
    file >> rows >> cols;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            file >> matrix[i][j];
        }
    }
    cout << "Матрица успешно прочитана из файла: " << filename << endl;
}

template<> int generateRandomValue<int>() { return rand() % 100; }
template<> double generateRandomValue<double>() { return (rand() % 1000) / 10.0; }
template<> char generateRandomValue<char>() { return 'A' + rand() % 26; }

void getMatrixSize(int& rows, int& cols, bool fromFile, const string& filename) {
    if (fromFile) {
        ifstream file(filename);
        file >> rows >> cols;
    } else {
        cout << "Введите количество строк и столбцов матрицы: ";
        cin >> rows >> cols;
    }
}

template<typename T>
T** manualInputToFile() {
    string filename;
    
    cout << "=== РУЧНОЙ ВВОД МАТРИЦЫ ===" << endl;
    getMatrixSize(rows, cols);
    
    cout << "Введите имя файла для сохранения матрицы: ";
    cin >> filename;
    
    T** matrix = createMatrix<T>(rows, cols);
    
    cout << endl << "Введите элементы матрицы:" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << "Элемент [" << i << "][" << j << "]: ";
            cin >> matrix[i][j];
        }
    }
    
    cout << endl << "Введенная матрица:" << endl;
    printMatrix(matrix, rows, cols);
    
    writeMatrixToFile(matrix, rows, cols, filename);
    return matrix;
}

template<typename T>
T** randomGenerateToFile() {
    string filename;
    
    cout << "=== СЛУЧАЙНАЯ ГЕНЕРАЦИЯ МАТРИЦЫ ===" << endl;
    getMatrixSize(rows, cols);
    
    cout << "Введите имя файла для сохранения матрицы: ";
    cin >> filename;
    
    T** matrix = createMatrix<T>(rows, cols);
    srand(time(0));
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = generateRandomValue<T>();
        }
    }
    
    cout << endl << "Сгенерированная матрица:" << endl;
    printMatrix(matrix, rows, cols);
    
    writeMatrixToFile(matrix, rows, cols, filename);
    return matrix;
}

template<typename T>
T** fileInputToConsole() {
    string filename;
    
    cout << "=== ЧТЕНИЕ МАТРИЦЫ ИЗ ФАЙЛА ===" << endl;
    cout << "Введите имя файла для чтения матрицы: ";
    cin >> filename;
    
    getMatrixSize(rows, cols, true, filename);
    
    T** matrix = createMatrix<T>(rows, cols);
    readMatrixFromFile(matrix, rows, cols, filename);
    
    cout << endl << "Прочитанная матрица:" << endl;
    printMatrix(matrix, rows, cols);
    return matrix;
}

template <typename T>
void search_max_minimal_el_in_matrix(T** matrix, int rows, int cols) {
    T max_minimal = numeric_limits<T>::lowest();
    bool found = false;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            T current = matrix[i][j];
            bool is_minimal = true;

            for (int d_i = -1; d_i <= 1 && is_minimal; ++d_i) {
                for (int d_j = -1; d_j <= 1 && is_minimal; ++d_j) {
                    if (d_i == 0 && d_j == 0) continue;
                    
                    int n_i = i + d_i, n_j = j + d_j;
                    if (n_i >= 0 && n_i < rows && n_j >= 0 && n_j < cols) {
                        if (current >= matrix[n_i][n_j]) {
                            is_minimal = false;
                        }
                    }
                }
            }

            if (is_minimal && (!found || current > max_minimal)) {
                max_minimal = current;
                found = true;
            }
        }
    }

    if (found) {
        cout << "Максимальный локальный минимум: " << max_minimal << endl;
    } else {
        cout << "Локальные минимумы не найдены." << endl;
    }
}