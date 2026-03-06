#ifndef PARTICIPANT_H
#define PARTICIPANT_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <map>

class ParticipantBase {
    public:
        virtual void print() const = 0;
        virtual ~ParticipantBase() {}
};

class Person {
    protected:
        std::string name;
        int age;
    public:
        int getAge() const {return age;}
        Person(const std::string& name, int age);
};

class Physical {
    protected:
        double height;
        double weight;
    public:
        double getWeight() const {return weight;}
        double getHeight() const {return height;}
        Physical(double height, double weight);
};

class TeamInfo {
    protected:
        std::string country;
        std::string team;
        int number;
    public:
        TeamInfo(const std::string& country, const std::string& team, int number);
};

class Participant : public ParticipantBase, public Person, public Physical, public TeamInfo {
    public:
        Participant(const std::string& name, int age, double height, double weight,
                    const std::string& country, const std::string& team, int number);
        void print() const override;
        friend std::ofstream& operator<<(std::ofstream& out, const Participant& a);
};

void Run(std::vector<Participant*>& participants);

#endif