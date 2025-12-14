#ifndef SIMPLE_MATRIX_H
#define SIMPLE_MATRIX_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <string>
#include <stdexcept>

class MatrixException : public std::runtime_error {
public:
    explicit MatrixException(const std::string& message) 
        : std::runtime_error(message) {}
};

class IOException : public std::runtime_error {
public:
    explicit IOException(const std::string& message) 
        : std::runtime_error(message) {}
};

template<typename T>
class Matrix {

    public:

        Matrix(int rows, int cols);
        Matrix(const Matrix& other);
        Matrix(Matrix&& other) noexcept;
        Matrix& operator=(const Matrix& other);
        Matrix& operator=(Matrix&& other) noexcept;
        ~Matrix();

        T** data() { return data_; }
        const T** data() const { return const_cast<const T**>(data_); }
        int rows() const { return rows_; }
        int cols() const { return cols_; }

        void FillFromConsole();
        void FillRandom();
        void Print() const;
        void WriteToFile(const std::string& filename) const;
        void ReadFromFile(const std::string& filename);

        T FindMaxLocalMinimum() const;


    private:

        T** data_;
        int rows_;
        int cols_;

        T GenerateRandomValue() const;
        bool IsLocalMinimum(int row, int col) const;
        void AllocateMemory();
        void DeallocateMemory();
        void CopyDataFrom(const Matrix& other);
        void ValidateIndices(int row, int col) const;
        void CheckNotEmpty() const;
        
};

template<> int Matrix<int>::GenerateRandomValue() const;
template<> double Matrix<double>::GenerateRandomValue() const;
template<> char Matrix<char>::GenerateRandomValue() const;

int GetInputChoice();
int GetDataTypeChoice();
void GetMatrixSize(int& rows, int& cols);
std::string GetFileName(const std::string& prompt);
void SetRussianLocale();

#endif