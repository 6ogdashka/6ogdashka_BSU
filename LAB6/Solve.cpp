#include "Simple_Matrix.h"
#include "russian.h"

template<typename T>
void ProcessMatrixType(int input_choice) {
    Matrix<T>* matrix = nullptr;
    
    try {
        if (input_choice == 1) {
            int rows, cols;
            GetMatrixSize(rows, cols);
            
            matrix = new Matrix<T>(rows, cols);
            matrix->FillFromConsole();
            
            const std::string filename = GetFileName(
                "Введите имя файла для сохранения матрицы: ");
            matrix->WriteToFile(filename);
            matrix->Print();
            
        } else if (input_choice == 2) {
            int rows, cols;
            GetMatrixSize(rows, cols);
            
            matrix = new Matrix<T>(rows, cols);
            matrix->FillRandom();
            
            const std::string filename = GetFileName(
                "Введите имя файла для сохранения матрицы: ");
            matrix->WriteToFile(filename);
            matrix->Print();
            
        } else if (input_choice == 3) {
            const std::string filename = GetFileName(
                "Введите имя файла для чтения матрицы: ");
            
            matrix = new Matrix<T>(1, 1);
            matrix->ReadFromFile(filename);
            matrix->Print();
        }
        
        std::cout << "\n=== ПОИСК МАКСИМАЛЬНОГО ЛОКАЛЬНОГО МИНИМУМА ===\n";
        const T result = matrix->FindMaxLocalMinimum();
        std::cout << "Максимальный локальный минимум: " << result << "\n";
        
        delete matrix;
        
    } catch (const std::exception& e) {
        if (matrix) delete matrix;
        throw;
    }
}

int main() {
    try {
        setRussianLocale();
        std::cout << "=== ПРОГРАММА ДЛЯ РАБОТЫ С МАТРИЦАМИ ===\n";
        
        const int input_choice = GetInputChoice();
        const int data_type = GetDataTypeChoice();
        
        std::cout << "\n";
        
        switch (data_type) {
            case 1:
                ProcessMatrixType<int>(input_choice);
                break;
            case 2:
                ProcessMatrixType<double>(input_choice);
                break;
            case 3:
                ProcessMatrixType<char>(input_choice);
                break;
            default:
                throw std::runtime_error("Неизвестный тип данных");
        }
        
    } catch (const std::exception& e) {
        std::cerr << "\nОшибка: " << e.what() << "\n";
        std::cerr << "Программа завершена с ошибкой.\n";
        return 1;
    }
    
    std::cout << "\nНажмите Enter для выхода...";
    std::cin.ignore();
    std::cin.get();
    return 0;
}