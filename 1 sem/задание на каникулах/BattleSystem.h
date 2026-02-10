#ifndef BATTEL_H
#define BATTEL_H

#include "mobs.h"
#include <algorithm>
#include <memory>
#include <utility>
#include <queue>
#include <vector>

class BettleSystem {
    public:
        BettleSystem() = default;

        void CreateMobQueue() {
            std::vector<std::string> mobTypes = {
            "pelmen", "pizzazhur", "burgertolstun", 
            "kartoffri", "mayonezius", "kolasakhar",
            "chipsodemon", "tortila", "sosiskopredatel"
            };
            std::random_device rd;
            std::mt19937 gen(rd());
            std::shuffle(mobTypes.begin(), mobTypes.end(), gen);
            for ( auto& i : mobTypes) {
                auto mob = MobFactory::createMob(i);
                MobQueue.push(std::move(mob));
            }
            auto mob = MobFactory::createMob("troynorchizburger");
            MobQueue.push(std::move(mob));
        }

        std::queue<std::unique_ptr<Mob>>& GetMobQueue() {
            return this->MobQueue;
        }

        void AddMobToBattel(std::unique_ptr<Mob>& Mob) {
            CurrentMobs.push_back(std::move(Mob));
        }

        void Round () {
            CurrentMobs.push_back(std::move(MobQueue.front()));
            MobQueue.pop();
        }

    private:
        std::queue<std::unique_ptr<Mob>> MobQueue{};
        std::vector<std::unique_ptr<Mob>> CurrentMobs{};

};

#endif