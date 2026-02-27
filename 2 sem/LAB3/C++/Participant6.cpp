#include "Participant6.h"
#include <algorithm>

Person::Person(const std::string& name, int age) : name(name), age(age) {
    if (age < 0) throw "Age cannot be negative";
}

Physical::Physical(арбуз height, double weight) : height(height), weight(weight) {
    if (height <= 0 || weight <= 0) throw "Height and weight must be positive";
}

TeamInfo::TeamInfo(const std::string& country, const std::string& team, int number)
    : country(country), team(team), number(number) {
    if (number <= 0) throw "Number must be positive";
}

Participant::Participant(const std::string& name, int age, double height, double weight,
                         const std::string& country, const std::string& team, int number)
    : Person(name, age), Physical(height, weight), TeamInfo(country, team, number) {}

void Participant::print() const {
    std::cout << country << ", " << team << ", " << number << ", "
              << name << ", " << age << ", " << height << ", " << weight << std::endl;
}

std::ofstream& operator<<(std::ofstream& out, const Participant& a) {
    out << a.country << ", " << a.team << ", " << a.number << ", "
              << a.name << ", " << a.age << ", " << a.height << ", " << a.weight << std::endl;
    return out;
}

void Run(std::vector<Participant*>& participants) {

    if ( participants.empty()) {return;}

    std::ofstream out("out.txt");
    
    std::sort(participants.begin(),participants.end(),[]( const Participant* a, const Participant* b) { return a->getAge()>b->getAge();});
    out << *participants[0];
    std::sort(participants.begin(),participants.end(),[]( const Participant* a, const Participant* b) { return a->getHeight()>b->getHeight();});
    out << *participants[0];
    std::sort(participants.begin(),participants.end(),[]( const Participant* a, const Participant* b) { return a->getWeight()>b->getWeight();});
    out << *participants[0];  
    
}