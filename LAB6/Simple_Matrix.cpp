#include "Simple_Matrix.h"

template<typename T>
Matrix<T>::Matrix(int rows, int cols) : rows_(rows), cols_(cols), data_(nullptr) {
    if (rows <= 0 || cols <= 0) {
        throw MatrixException("Некорректные размеры матрицы");
    }
    AllocateMemory();
}

template<typename T>
Matrix<T>::Matrix(const Matrix& other) : rows_(other.rows_), cols_(other.cols_), data_(nullptr) {
    AllocateMemory();
    CopyDataFrom(other);
}

template<typename T>
Matrix<T>::Matrix(Matrix&& other) noexcept 
    : rows_(other.rows_), cols_(other.cols_), data_(other.data_) {
    other.rows_ = 0;
    other.cols_ = 0;
    other.data_ = nullptr;
}

template<typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix& other) {
    if (this != &other) {
        DeallocateMemory();
        rows_ = other.rows_;
        cols_ = other.cols_;
        AllocateMemory();
        CopyDataFrom(other);
    }
    return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::operator=(Matrix&& other) noexcept {
    if (this != &other) {
        DeallocateMemory();
        rows_ = other.rows_;
        cols_ = other.cols_;
        data_ = other.data_;
        other.rows_ = 0;
        other.cols_ = 0;
        other.data_ = nullptr;
    }
    return *this;
}

template<typename T>
Matrix<T>::~Matrix() {
    DeallocateMemory();
}

template<typename T>
void Matrix<T>::AllocateMemory() {
    data_ = new T*[rows_];
    for (int i = 0; i < rows_; ++i) {
        data_[i] = new T[cols_];
    }
}

template<typename T>
void Matrix<T>::DeallocateMemory() {
    if (data_) {
        for (int i = 0; i < rows_; ++i) {
            delete[] data_[i];
        }
        delete[] data_;
        data_ = nullptr;
    }
    rows_ = 0;
    cols_ = 0;
}

template<typename T>
void Matrix<T>::CopyDataFrom(const Matrix& other) {
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            data_[i][j] = other.data_[i][j];
        }
    }
}

template<typename T>
void Matrix<T>::CheckNotEmpty() const {
    if (!data_ || rows_ == 0 || cols_ == 0) {
        throw MatrixException("Матрица пустая или не инициализирована");
    }
}

template<typename T>
void Matrix<T>::ValidateIndices(int row, int col) const {
    if (row < 0 || row >= rows_ || col < 0 || col >= cols_) {
        throw MatrixException("Некорректные индексы матрицы");
    }
}

template<typename T>
void Matrix<T>::FillFromConsole() {
    CheckNotEmpty();
    std::cout << "Введите " << rows_ * cols_ << " элементов матрицы " 
              << rows_ << "x" << cols_ << ":\n";
    
    for (int i = 0; i < rows_; ++i) {
        std::cout << "Строка " << i << ": ";
        for (int j = 0; j < cols_; ++j) {
            if (!(std::cin >> data_[i][j])) {
                throw MatrixException("Ошибка ввода данных");
            }
        }
    }
}

template<typename T>
T Matrix<T>::GenerateRandomValue() const {
    return static_cast<T>(rand() % 100);
}

template<typename T>
void Matrix<T>::FillRandom() {
    CheckNotEmpty();
    srand(static_cast<unsigned>(time(nullptr)));
    
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            data_[i][j] = GenerateRandomValue();
        }
    }
}

template<typename T>
void Matrix<T>::Print() const {
    CheckNotEmpty();
    std::cout << "Матрица " << rows_ << "x" << cols_ << ":\n";
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            std::cout << data_[i][j] << " ";
        }
        std::cout << "\n";
    }
}

template<typename T>
void Matrix<T>::WriteToFile(const std::string& filename) const {
    CheckNotEmpty();
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw IOException("Не удалось открыть файл для записи: " + filename);
    }
    
    file << rows_ << " " << cols_ << "\n";
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            file << data_[i][j] << " ";
        }
        file << "\n";
    }
    
    if (file.fail()) {
        throw IOException("Ошибка записи в файл: " + filename);
    }
    
    file.close();
    std::cout << "Матрица записана в файл: " << filename << "\n";
}

template<typename T>
void Matrix<T>::ReadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw IOException("Не удалось открыть файл для чтения: " + filename);
    }
    
    int new_rows, new_cols;
    if (!(file >> new_rows >> new_cols) || new_rows <= 0 || new_cols <= 0) {
        throw IOException("Некорректные размеры в файле: " + filename);
    }
    
    DeallocateMemory();
    rows_ = new_rows;
    cols_ = new_cols;
    AllocateMemory();
    
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            if (!(file >> data_[i][j])) {
                throw IOException("Ошибка чтения данных из файла: " + filename);
            }
        }
    }
    
    if (file.fail() && !file.eof()) {
        throw IOException("Ошибка формата файла: " + filename);
    }
    
    file.close();
    std::cout << "Матрица прочитана из файла: " << filename << "\n";
}

template<typename T>
bool Matrix<T>::IsLocalMinimum(int row, int col) const {
    ValidateIndices(row, col);
    const T current = data_[row][col];
    
    for (int di = -1; di <= 1; ++di) {
        for (int dj = -1; dj <= 1; ++dj) {
            if (di == 0 && dj == 0) continue;
            
            const int neighbor_row = row + di;
            const int neighbor_col = col + dj;
            
            if (neighbor_row >= 0 && neighbor_row < rows_ &&
                neighbor_col >= 0 && neighbor_col < cols_) {
                if (current > data_[neighbor_row][neighbor_col]) {
                    return false;
                }
            }
        }
    }
    return true;
}

template<typename T>
T Matrix<T>::FindMaxLocalMinimum() const {
    CheckNotEmpty();
    bool found = false;
    T max_minimum = std::numeric_limits<T>::lowest();
    
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            if (IsLocalMinimum(i, j)) {
                if (!found || data_[i][j] > max_minimum) {
                    max_minimum = data_[i][j];
                    found = true;
                }
            }
        }
    }
    
    if (!found) {
        throw MatrixException("Локальные минимумы не найдены");
    }
    
    return max_minimum;
}

template<> int Matrix<int>::GenerateRandomValue() const {
    return rand() % 100;
}

template<> double Matrix<double>::GenerateRandomValue() const {
    return (rand() % 1000) / 10.0;
}

template<> char Matrix<char>::GenerateRandomValue() const {
    return 'A' + rand() % 26;
}


int GetInputChoice() {
    int choice;
    std::cout << "\nВыберите способ ввода матрицы:\n";
    std::cout << "1 - Ручной ввод\n";
    std::cout << "2 - Случайная генерация\n";
    std::cout << "3 - Чтение из файла\n";
    std::cout << "Ваш выбор: ";
    std::cin >> choice;
    
    if (std::cin.fail() || choice < 1 || choice > 3) {
        throw std::runtime_error("Некорректный выбор способа ввода");
    }
    return choice;
}

int GetDataTypeChoice() {
    int data_type;
    std::cout << "\nВыберите тип данных матрицы:\n";
    std::cout << "1 - Целые числа (int)\n";
    std::cout << "2 - Вещественные числа (double)\n";
    std::cout << "3 - Символы (char)\n";
    std::cout << "Ваш выбор: ";
    std::cin >> data_type;
    
    if (std::cin.fail() || data_type < 1 || data_type > 3) {
        throw std::runtime_error("Некорректный тип данных");
    }
    return data_type;
}

void GetMatrixSize(int& rows, int& cols) {
    std::cout << "Введите количество строк и столбцов матрицы: ";
    std::cin >> rows >> cols;
    
    if (std::cin.fail() || rows <= 0 || cols <= 0) {
        throw std::runtime_error("Некорректные размеры матрицы");
    }
}

std::string GetFileName(const std::string& prompt) {
    std::string filename;
    std::cout << prompt;
    std::cin >> filename;
    
    if (filename.empty()) {
        throw std::runtime_error("Имя файла не может быть пустым");
    }
    return filename;
}

template class Matrix<int>;
template class Matrix<double>;
template class Matrix<char>;