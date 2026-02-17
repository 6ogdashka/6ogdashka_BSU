#include <iostream>
#include <string>
#include <cctype>
#include <regex>

void Task1() {
    std::string str{};
    std::cout << "Enter str: ";
    std::getline(std::cin,str);
    std::string current_numb{};

    for ( auto i : str) {
        if (isdigit(i) ) {
            current_numb+=i;
            continue;
        } else if (!current_numb.empty() ) {
            std::cout << current_numb << "\n";
            current_numb.clear();
        }
    }
    if ( !current_numb.empty() ) {
        std::cout << current_numb << "\n";
        current_numb.clear();
    }
}

void Task2() {
    std::string str{};
    std::cout << "Enter str: ";
    std::getline(std::cin,str);
    
    std::regex isntdigit(R"(\D)");
    str = std::regex_replace(str,isntdigit," ");
    std::stringstream stream(str);
    std::string current_number;
    while ( stream >> current_number) {
        std::cout << current_number << "\n\n";
    } 
}

int main() {
    Task2();
    Task1();
    return 0;
}