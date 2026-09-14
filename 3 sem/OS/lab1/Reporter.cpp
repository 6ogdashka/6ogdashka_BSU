#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include "employee.h"

void Reporter(const std::string& BinFileName, const std::string& ReportName, double HoursCost) {
    std::ifstream input(BinFileName, std::ios::binary);
    std::ofstream output(ReportName);

    output << "Отчет по файлу \"" << BinFileName << "\"\n";
    output << "Номер сотрудника, имя сотрудника, часы, зарплата\n";

    std::vector<employee> employees;
    employee buff{};
    while (input.read(reinterpret_cast<char*>(&buff), sizeof(buff))) {
        employees.push_back(buff);
    }

    std::sort(employees.begin(), employees.end());

    for (const auto& emp : employees) {
        output << emp.num << " " << emp.name << " " << emp.hours << " " << emp.hours * HoursCost << "\n";
    }
}

int main(int argc, char* argv[]) {
    std::string BinFileName = argv[1];
    std::string ReportName  = argv[2];
    double HoursCost = std::stod(argv[3]);

    Reporter(BinFileName, ReportName, HoursCost);
    return 0;
}