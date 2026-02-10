#include "Employee.h"

Employee::Employee(const std::string& a, size_t b) 
    : surname_(a), children_(b) {}

Employee::Employee(Employee&& a) 
    : surname_(std::move(a.surname_)), children_(a.children_) { a.children_ = 0; }

Employee::Employee(const Employee& a) : surname_(a.surname_), children_(a.children_){}

std::string Employee::getS() const {

    return this->surname_;
}

size_t Employee::getCh() const
{
    return this->children_;
}

Employee& Employee::setS(const std::string& a)
{
    this->surname_ = a;
    return *this;
}

Employee& Employee::setCH(size_t a)
{
    this->children_ = a;
    return *this;
}

Employee& Employee::operator=(const Employee& a)
{
    this->surname_ = a.surname_;
    this->children_ = a.children_;
    return *this;
}

std::ofstream& operator<<(std::ofstream& out, Employee& a)
{
    return out;
}

bool Employee::operator<( const Employee& a) {
    if ( this->surname_ < a.surname_) {
        return true;
    } else {
        return this->children_ < a.children_;
    }
}
