#ifndef BAHDAN_H
#define BAHDAN_H

#include <cstddef>

class Bahdan {
    public:
        Bahdan() : fat_(100), discipline(0){};

        size_t GetBahdanFat() {
            return fat_;
        }

        void GainFatToBahdan(int fat ) {
            fat_+=fat;
        }

    protected:
        size_t fat_{100};
        size_t discipline{0};
};
#endif