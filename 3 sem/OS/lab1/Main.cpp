#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "employee.h"

void RunProcess(const std::string& program, const std::vector<std::string>& args) {
    std::vector<char*> argv;
    argv.push_back(const_cast<char*>(program.c_str()));
    for (const auto& a : args) {
        argv.push_back(const_cast<char*>(a.c_str()));
    }
    argv.push_back(nullptr);

    pid_t pid = fork();
    if (pid == 0) {
        execv(program.c_str(), argv.data());
        perror("execv");
        _exit(1);
    }

    int status = 0;
    waitpid(pid, &status, 0);
}

void PrintBinaryFile(const std::string& BinFileName) {
    std::ifstream input(BinFileName, std::ios::binary);
    employee buff{};
    while (input.read(reinterpret_cast<char*>(&buff), sizeof(buff))) {
        std::cout << buff << "\n";
    }
}

void PrintTextFile(const std::string& FileName) {
    std::ifstream input(FileName);
    std::string line;
    while (std::getline(input, line)) {
        std::cout << line << "\n";
    }
}

int main() {
    std::string BinFileName;
    int n;

    std::cout << "Введите имя бинарного файла: ";
    std::cin >> BinFileName;
    std::cout << "Введите количество записей: ";
    std::cin >> n;

    RunProcess("./Creator.out",
                 { BinFileName, std::to_string(n) });

    std::cout << "\nСодержимое бинарного файла:\n";
    PrintBinaryFile(BinFileName);

    std::string ReportName;
    double HoursCost;
    std::cout << "\nВведите имя файла отчёта: ";
    std::cin >> ReportName;
    std::cout << "Введите оплату за час: ";
    std::cin >> HoursCost;

    RunProcess("./Reporter.out",
               { BinFileName, ReportName, std::to_string(HoursCost) });

    PrintTextFile(ReportName);

    return 0;
}