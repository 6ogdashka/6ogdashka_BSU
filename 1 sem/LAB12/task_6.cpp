#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <stdexcept>
#include <cctype>
#include "russian.h"

struct SMark {
    std::string subject;
    int mark;
};

struct SStudData {
    std::string name;
    int record_book_number;
    std::vector<SMark> marks;
};

std::string TrimString(const std::string& str) {
    size_t start = 0;
    while (start < str.length() && std::isspace(str[start])) {
        ++start;
    }
    
    size_t end = str.length();
    while (end > start && std::isspace(str[end - 1])) {
        --end;
    }
    
    return str.substr(start, end - start);
}

void ValidateStudent(const SStudData& student) {
    if (student.name.empty()) {
        throw std::invalid_argument("Имя студента не может быть пустым");
    }
    
    if (student.record_book_number <= 0) {
        throw std::invalid_argument("Номер зачетки должен быть положительным");
    }
    
    for (const SMark& mark : student.marks) {
        if (mark.subject.empty()) {
            throw std::invalid_argument("Название предмета не может быть пустым");
        }
        
        if (mark.mark < 1) {
            throw std::invalid_argument("Оценка должна быть не менее 1");
        }
    }
}

SStudData ParseStudentLine(const std::string& line) {
    std::istringstream stream(line);
    SStudData student;
    
    if (!(stream >> student.name)) {
        throw std::invalid_argument("Не удалось прочитать имя студента");
    }
    
    if (!(stream >> student.record_book_number)) {
        throw std::invalid_argument("Не удалось прочитать номер зачетки");
    }
    
    std::string mark_pair;
    while (stream >> mark_pair) {
        size_t colon_pos = mark_pair.find(':');
        if (colon_pos == std::string::npos) {
            throw std::invalid_argument("Неверный формат оценки: " + mark_pair);
        }
        
        SMark mark;
        mark.subject = mark_pair.substr(0, colon_pos);
        
        try {
            mark.mark = std::stoi(mark_pair.substr(colon_pos + 1));
        } catch (const std::exception&) {
            throw std::invalid_argument("Неверный формат оценки: " + mark_pair);
        }
        
        student.marks.push_back(mark);
    }
    
    ValidateStudent(student);
    return student;
}

std::map<int, SStudData> ReadStudentsFromFile(const std::string& filename) {
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть файл: " + filename);
    }
    
    std::map<int, SStudData> students;
    std::string line;
    int line_number = 0;
    
    while (std::getline(file, line)) {
        ++line_number;
        
        std::string trimmed_line = TrimString(line);
        if (trimmed_line.empty()) {
            continue;
        }
        
        try {
            SStudData student = ParseStudentLine(trimmed_line);
            
            if (students.count(student.record_book_number) > 0) {
                std::cerr << "Предупреждение: студент с номером " 
                         << student.record_book_number 
                         << " уже существует. Заменяем.\n";
            }
            
            students[student.record_book_number] = student;
            
        } catch (const std::invalid_argument& e) {
            throw std::runtime_error("Ошибка в строке " + std::to_string(line_number) + 
                                   ": " + e.what());
        }
    }
    
    file.close();
    
    if (students.empty()) {
        throw std::runtime_error("Файл не содержит данных о студентах");
    }
    
    return students;
}

std::string GetSubjectFromUser() {
    std::string subject;
    
    std::cout << "Введите название предмета: ";
    
    if (!std::getline(std::cin, subject)) {
        throw std::runtime_error("Ошибка при чтении названия предмета");
    }
    
    std::string trimmed_subject = TrimString(subject);
    
    if (trimmed_subject.empty()) {
        throw std::invalid_argument("Название предмета не может быть пустым");
    }
    
    return trimmed_subject;
}

void PrintStudentsBySubject(const std::map<int, SStudData>& students,
                           const std::string& subject) {
    std::cout << "\nСтуденты, сдававшие предмет \"" << subject << "\":\n";
    std::cout << "========================================\n";
    
    bool found = false;
    
    for (const auto& pair : students) {
        const SStudData& student = pair.second;
        
        for (const SMark& mark : student.marks) {
            if (mark.subject == subject) {
                found = true;
                
                std::cout << "Номер зачетки: " << student.record_book_number << "\n";
                std::cout << "ФИО: " << student.name << "\n";
                std::cout << "Оценка по предмету: " << mark.mark << "\n";
                std::cout << "----------------------------------------\n";
                
                break;
            }
        }
    }
    
    if (!found) {
        std::cout << "Студентов, сдававших предмет \"" << subject << "\", не найдено.\n";
    }
}

void SolveTask() {
    const std::string filename = "input.txt";
    
    std::map<int, SStudData> students = ReadStudentsFromFile(filename);
    
    std::string subject = GetSubjectFromUser();
    
    PrintStudentsBySubject(students, subject);
}

int main() {
    setRussianLocale();
    
    try {
        SolveTask();
        return 0;
        
    } catch (const std::invalid_argument& e) {
        std::cerr << "Ошибка ввода: " << e.what() << "\n";
        return 1;
        
    } catch (const std::runtime_error& e) {
        std::cerr << "Ошибка выполнения: " << e.what() << "\n";
        return 1;
        
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << "\n";
        return 1;
        
    } catch (...) {
        std::cerr << "Неизвестная ошибка!\n";
        return 1;
    }
}