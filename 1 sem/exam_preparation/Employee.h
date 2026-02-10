#pragma once
#include <string>
class Employee
{
public:
    Employee() = delete;
    Employee(const std::string&, size_t);
    Employee(Employee&&);
    Employee(const Employee&);
    ~Employee() = default;

    std::string getS() const;
    size_t getCh() const;
    Employee& setS(const std::string&);
    Employee& setCH(size_t);

    friend std::ostream& operator << (std::ostream&, Employee&);
    Employee& operator = (const Employee&);
    bool operator < (const Employee&);


private:
    std::string surname_{};
    size_t children_{};
};

