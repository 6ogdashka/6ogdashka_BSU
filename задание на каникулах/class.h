#ifndef CLASS_H
#define CLASS_H

#include <cstddef>
#include <iostream>
#include <ostream>
#include "weapon.h"


class FatFighter {
    public:

        FatFighter LvlUp () {
            ++lvl_;
            fat_-=5;
            std::cout << "Вы подняли уровень, вам доступно очко улучшения\n";
            std::cout << "Куда бы вы хотели его вложить\n";
            std::cout << "1 - Сила Воли\n";
            std::cout << "2 - Дисциплина\n";
            std::cout << "3 - Энергия\n";
            std::cout << " Ваш выбор: ";
            int input_choice{};
            std::cin >> input_choice;
            if ( input_choice == 1) {
                ++willpower_;
                return *this;
            } else if ( input_choice == 2) {
                discipline_+=5;
                return *this;
            } else {
                energy_+=5;
                return *this;;
            }
        }


        bool IronWill() {
            return(fat_<= 50);
        }

    private:
        size_t lvl_{};
        size_t fat_{100};
        size_t willpower_{5};
        size_t discipline_{10};
};

#endif