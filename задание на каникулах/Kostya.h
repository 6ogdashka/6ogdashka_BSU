#ifndef KOSTYA_H
#define KOSTYA_H

#include <cstddef>
#include "Bahdan.h"

class Kostya {

    Kostya& LvlUp() {
        ++lvl_;
        dmg_+=2;
        return *this;
    }

    int DealDamage () {
        if (Bahdan_.GetBahdanFat() > 75) {
            return (dmg_-3);
        } else {
        return dmg_;
        }
    }

    

    protected:
        int lvl_{};
        int dmg_{7};
        Bahdan Bahdan_;


};

#endif