#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <sstream>

using namespace std;

struct SMark {
    string Subject;
    int Mark;
};

struct SStudData {
    string Name;
    int Number;
    vector<SMark> Marks;
};

void printStudentsBySubject(const map<int, SStudData>& students, const string& subject);

int main() {
    map<int, SStudData> students;
    
    ifstream file("input.txt");
    if (!file) {
        cerr << "Ошибка открытия файла!" << endl;
        return 1;
    }
    
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        
        SStudData student;
        istringstream iss(line);
        
        iss >> student.Name;
        
        iss >> student.Number;
        
        string mark_pair;
        while (iss >> mark_pair) {
            size_t colonPos = mark_pair.find(':');
            if (colonPos != string::npos) {
                SMark mark;
                mark.Subject = mark_pair.substr(0, colonPos);
                mark.Mark = stoi(mark_pair.substr(colonPos + 1));
                student.Marks.push_back(mark);
            }
        }
        
        students[student.Number] = student;
    }
    
    file.close();
    
    string subject;
    cout << "Введите название предмета: ";
    getline(cin, subject);
    
    printStudentsBySubject(students, subject);
    
    return 0;
}

void printStudentsBySubject(const map<int, SStudData>& students, const string& subject) {
    cout << "Студенты, сдававшие предмет \"" << subject << "\":" << endl;
    cout << "----------------------------------------" << endl;
    
    bool found = false;
    for (const auto& student : students) {
        const SStudData& studData = student.second;
        for (const auto& mark : studData.Marks) {
            if (mark.Subject == subject) {
                found = true;

                cout << "Номер зачетки: " << studData.Number << endl;
                cout << "ФИО: " << studData.Name << endl;
                cout << "Оценка по предмету: " << mark.Mark << endl;
                cout << "\n----------------------------------------" << endl;

                break; 
            }
        }
    }
    
    if (!found) {
        cout << "Студентов, сдававших предмет \"" << subject << "\", не найдено." << endl;
    }
}