#include "Participant6.h"

int main() {
    
    std::vector<Participant*> participants;

    try {
        participants.push_back(new Participant("Ivan", 25, 180.5, 75.0, "Russia", "Spartak", 10));
        participants.push_back(new Participant("John", 30, 192.0, 90.5, "USA", "Lakers", 23));
        participants.push_back(new Participant("Alex", 20, 175.0, 82.0, "Germany", "Bayern", 7));

        Run(participants);
    } catch (...) {}

    for (Participant* p : participants) {
        delete p;
    }

    return 0;
}