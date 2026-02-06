#include <cctype>
#include <cstring>
#include <istream>
#include <iostream>
#include <vector>
#include "Employee.cpp"
#include "Employee.h"
#include <algorithm>

bool Compare(const Employee& a, const Employee& b)
{
    std::string copy_first{a.getS()};
    copy_first[0] = tolower(copy_first[0]);
    std::string
    if (a.getS() < b.getS()) {
        return true;
    }
    else {
        return b.getCh() < a.getCh();
    }
}

std::vector<size_t> CreateNumVector ();
std::vector<std::string> CreateStrVector();
template <typename T>
void PickSort ( std::vector<Employee>& vec);

int main() {

    std::vector<std::string> allSurnames = CreateStrVector();
    std::vector<size_t> allNumbers = CreateNumVector();
    std::vector<Employee> employees;
    int j;
    for (size_t i{}; i < allSurnames.size(); ++i) {
        Employee emp(allSurnames[i], 0);
        if ((j < allNumbers.size()) && (allNumbers[j] < 10)) {
            emp.setCH(allNumbers[j]);
            employees.push_back(emp);
            ++j;
        }
        else if (j < allNumbers.size()) {
            while (j < allNumbers.size()) {
                if (allNumbers[j] < 10) {
                    emp.setCH(allNumbers[j]);
                    break;
                }
                ++j;
            }
        } else {
            size_t a;
            std::cout << "Введите пожалуйства количество детей у работника " << allSurnames[i] << ": ";
            while (true) {
                std::cin >> a;
                if ((a < 10) && (a >= 1)) {
                    emp.setCH(a);
                    break;
                }
                else {
                    std::cout << "-1";
                }
            }
        }
    }
    PickSort(employees);
    sort(employees.begin(), employees.end(), Compare);
    return 0;

}
std::vector<size_t> CreateNumVector () {

    FILE* file = fopen("numbers.txt","r");

    char d[100];
    char str[100];
    char* result = (char*)malloc(1);
    result[0] = 0;

    fgets(d,100,file);
    d[strcspn(d, "\n")] = 0;

    while (fgets(str,100,file)) { 

        str[strcspn(str, "\n")] = 0;
        char* t = strtok(str,d);
        while (t) {

            result = (char*)realloc(result,strlen(result) + strlen(t) + (result[0]?2:1));
            strcat(result,t);
            strcat(result," ");
            t = strtok(NULL,d);

        }
    }
    fclose(file);
    
    char* t = strtok(result," ");
    std::vector<size_t> num_result{};

    while (t) {
        num_result.push_back(atoi(t));
        t = strtok(NULL," ");
    }
    return num_result;
}

std::vector<std::string> CreateStrVector() {
    FILE* file = fopen("strings.txt","r");

    char d[100];
    char str[100];
    char* result = (char*)malloc(1);
    result[0] = 0;

    fgets(d,100,file);
    d[strcspn(d, "\n")] = 0;

    while (fgets(str,100,file)) { 

        str[strcspn(str, "\n")] = 0;
        char* t = strtok(str,d);
        while (t) {

            result = (char*)realloc(result,strlen(result) + strlen(t) + (result[0]?2:1));
            strcat(result,t);
            strcat(result," ");
            t = strtok(NULL,d);

        }
    }
    fclose(file);

    std::vector<std::string> str_result{};
    char* t = strtok(result," ");

    while(t) {
        str_result.push_back(t);
        t = strtok(NULL," ");
    }
    return str_result;
}
template <typename T>
void PickSort ( std::vector<T>& vec) {

    for ( size_t i{}; i < vec.size(); ++i) {
        T min = vec[i];
        size_t pos{i};
        for ( size_t j {i}; j < vec.size();++j) {
            if ( vec[j] < min ) {
                min = vec[j];
                pos = j;
            }
        }
        std::swap(vec[i],vec[pos]);
    }
}