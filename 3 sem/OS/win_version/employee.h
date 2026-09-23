#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <iostream>

struct employee {
    int num{};
    char name[10];
    double hours{};

    bool operator<(const employee& other) const {
        return num < other.num;
    }

    friend std::istream& operator>>(std::istream& in, employee& emp) {
        in >> emp.num >> emp.name >> emp.hours;
        return in;
    }

    friend std::ostream& operator<<(std::ostream& out, const employee& emp) {
        out << emp.num << " " << emp.name << " " << emp.hours << " ";
        return out;
    }
};

#endif