#include <iostream>
#include <fstream>
#include <clocale>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <stdexcept>

namespace  {

    struct Student {
        std::string name;
        int course;
        int group;

        friend std::ofstream& operator<<(std::ofstream& ofile, const Student& a) {
            ofile << a.name << " " << a.course << " " << a.group << '\n';
            return ofile;
        }
    };

void ValidateStudent(const Student& student) {
    if (student.name.empty()) {
        throw std::invalid_argument("Имя студента не может быть пустым");
    }
    
    if (student.course <= 0) {
        throw std::invalid_argument("Номер курса должен быть положительным");
    }
    
    if (student.group <= 0) {
        throw std::invalid_argument("Номер группы должен быть положительным");
    }
}

std::string str_toupper(std::string s)
{
    std::transform(s.begin(), s.end(), s.begin(),
                   [](unsigned char c){ return std::toupper(c); }
                  );
    return s;
}

Student ParseStudentLine(const std::string& line) {
    std::istringstream iss(line);
    Student student;
    
    if (!(iss >> student.name)) {
        throw std::invalid_argument("Не удалось прочитать имя студента");
    }
    
    if (!(iss >> student.course)) {
        throw std::invalid_argument("Не удалось прочитать номер курса");
    }
    
    if (!(iss >> student.group)) {
        throw std::invalid_argument("Не удалось считать номер группы");
    }
    setlocale(LC_ALL, "Russian");
    std::string result = student.name;
    result = str_toupper(result);
    student.name = result;
    std::wcout << L"student.name" << '\n';
    ValidateStudent(student);
    return student;
}


std::vector<Student> ReadStudentsFromFile(const std::string& filename) {
    std::ifstream file(filename);
    
    if (!file) {
        throw std::runtime_error("Не удалось открыть файл: " + filename);
    }
    
    std::vector<Student> students;
    std::string line;
    int line_number = 0;
    
    while ( std::getline(file,line)) {
        Student current_student = ParseStudentLine(line);
        students.push_back(current_student);
    }
    
    file.close();
    
    if (students.empty()) {
        throw std::runtime_error("Файл не содержит данных о студентах");
    }
    
    return students;
}

bool Compare(const Student& a, const Student& b) {
    return a.name < b.name;
}

void Generate_Fio_txt_File( const std::vector<Student>& students) {
    std::ofstream ofile("Fio.txt");
    std::vector<Student> Fio(students.begin(),students.end());
    sort(Fio.begin(),Fio.end(), Compare);
    while (Fio.size() != 0) {
         ofile << Fio.front();
         Fio.erase(Fio.begin());
    }
}

bool SpecialCompare(const Student& a, const Student& b) {
    if ( a.course != b.course) {
        return a.course < b.course;
    } else if ( a.group != b.group) {
        return a.group < b.group;
    } else {
        return a.name < b.name;
    }
}

void Generate_Group_txt_File ( const std::vector<Student>& students) {
    std::ofstream ofile("Group.txt");
    std::vector<Student> Group(students.begin(),students.end());
    sort(Group.begin(),Group.end(),SpecialCompare);
    while (Group.size() != 0) {
        ofile << Group.front();
        Group.erase(Group.begin());
    }
}

}

int main() {
    try {
    setRussianLocale();
    std::vector<Student> students = ReadStudentsFromFile("Students.txt");
    Generate_Fio_txt_File(students);
    Generate_Group_txt_File(students);
    return 0;
    } catch ( std::runtime_error& e) { std::cout << "Ошибка: " << e.what(); }
      catch ( std::invalid_argument& e) { std::cout << "Ошибка: " << e.what();}
}

