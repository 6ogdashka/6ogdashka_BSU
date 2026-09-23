#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <windows.h>
#include "employee.h"

void RunProcess(const std::string& program, const std::vector<std::string>& args) {
    std::string cmd = program;
    for (const auto& a : args) {
        cmd += " " + a;
    }

    STARTUPINFOA si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    if (CreateProcessA(NULL, cmd.data(), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        WaitForSingleObject(pi.hProcess, INFINITE);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
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
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    std::string BinFileName;
    int n;

    std::cout << "Введите имя бинарного файла: ";
    std::cin >> BinFileName;
    std::cout << "Введите количество записей: ";
    std::cin >> n;

    RunProcess("Creator.exe", { BinFileName, std::to_string(n) });

    std::cout << "\nСодержимое бинарного файла:\n";
    PrintBinaryFile(BinFileName);

    std::string ReportName;
    double HoursCost;
    std::cout << "\nВведите имя файла отчёта: ";
    std::cin >> ReportName;
    std::cout << "Введите оплату за час: ";
    std::cin >> HoursCost;

    RunProcess("Reporter.exe", { BinFileName, ReportName, std::to_string(HoursCost) });

    PrintTextFile(ReportName);

    return 0;
}