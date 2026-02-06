#include <iostream>
#include <string>
#include <memory>
#include <random>
#include <vector>
#include <functional>
#include <cassert>

class Mob {
protected:
    std::string name_;
    int maxHealthPoints_;
    int currentHealthPoints_;
    int fatAttack_;
    std::string description_;
    int turnCount_;
    
public:

    Mob(const std::string& name, int healthPoints, int fatAttack, const std::string& description)
        : name_(name)
        , maxHealthPoints_(healthPoints)
        , currentHealthPoints_(healthPoints)
        , fatAttack_(fatAttack)
        , description_(description)
        , turnCount_(0) {}
    
    virtual ~Mob() = default;
    
    const std::string& getName() const { return name_; }
    
    int getHealthPoints() const { return currentHealthPoints_; }
    
    int getMaxHealthPoints() const { return maxHealthPoints_; }
    
    int getFatAttack() const { return fatAttack_; }
    

    const std::string& getDescription() const { return description_; }
    
    bool isAlive() const { return currentHealthPoints_ > 0; }
    
    void takeDamage(int damage) {
        int actualDamage = calculateActualDamage(damage);
        currentHealthPoints_ = std::max(0, currentHealthPoints_ - actualDamage);
    }
    
    virtual int performAttack() {
        ++turnCount_;
        return calculateActualAttack();
    }
    
    virtual void reset() {
        currentHealthPoints_ = maxHealthPoints_;
        turnCount_ = 0;
        onReset();
    }
    
    std::string getStatus() const {
        return name_ + ": " + std::to_string(currentHealthPoints_) + 
               "/" + std::to_string(maxHealthPoints_) + " HP";
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Mob& mob) {
        os << mob.name_ << " (HP: " << mob.currentHealthPoints_ 
           << "/" << mob.maxHealthPoints_ << ")";
        return os;
    }
    
protected:

    virtual int calculateActualDamage(int damage) = 0;
    
    virtual int calculateActualAttack() = 0;
    
    virtual void onReset() {}
};


class Pelmen : public Mob {
private:
    bool friendCalled_;
    
public:
    Pelmen() 
        : Mob("Пельмений", 15, 5, 
              "Вредный и липкий! Прячется в супах, маскируясь под невинную еду. "
              "С каждым укусом добавляет по 100 калорий!")
        , friendCalled_(false) {}
    
protected:
    int calculateActualDamage(int damage) override {
        return damage;
    }
    
    int calculateActualAttack() override {
        if (turnCount_ == 3 && !friendCalled_ && isAlive()) {
            currentHealthPoints_ += 3;
            friendCalled_ = true;
            std::cout << "  " << name_ << " позвал друга! +3 HP" << std::endl;
        }
        return fatAttack_;
    }
    
    void onReset() override {
        friendCalled_ = false;
    }
};

class PizzaZhur : public Mob {
private:
    int pepperoniBonus_;
    
public:
    PizzaZhur()
        : Mob("ПиццеЖор", 25, 8,
              "Круглый обманщик с сырной улыбкой. Его корка хрустит так же громко, "
              "как обещания Богдана 'начать с понедельника'.")
        , pepperoniBonus_(0) {}
    
protected:
    int calculateActualDamage(int damage) override {
        return damage;
    }
    
    int calculateActualAttack() override {
        // ПиццеЖор каждый ход бросает кусочек пепперони
        pepperoniBonus_++;
        int totalAttack = fatAttack_ + pepperoniBonus_;
        
        if (pepperoniBonus_ > 1) {
            std::cout << "  " << name_ << " бросил пепперони! Атака +" 
                      << pepperoniBonus_ << std::endl;
        }
        
        return totalAttack;
    }
    
    void onReset() override {
        pepperoniBonus_ = 0;
    }
};

class BurgerTolstun : public Mob {
private:
    bool bunProtectionActive_;
    
public:
    BurgerTolstun()
        : Mob("БургероТолстун", 30, 10,
              "Многослойный мучитель. Каждый слой — новое испытание: "
              "котлета, сыр, бекон, майонез... И всё это между двумя булками!")
        , bunProtectionActive_(true) {}
    
protected:
    int calculateActualDamage(int damage) override {
        // БургероТолстун имеет булочную защиту
        if (bunProtectionActive_) {
            int actualDamage = damage / 2;
            bunProtectionActive_ = false;
            std::cout << "  Булочная защита поглотила часть урона! Урон: " 
                      << actualDamage << " вместо " << damage << std::endl;
            return actualDamage;
        }
        return damage;
    }
    
    int calculateActualAttack() override {
        // БургероТолстун атакует стабильно
        return fatAttack_;
    }
    
    void onReset() override {
        bunProtectionActive_ = true;
    }
};

class KartofFri : public Mob {
public:
    KartofFri()
        : Mob("КартофьФри", 20, 6,
              "Хрустящие предатели. Кажется, их много, и все они действуют заодно! "
              "Особенно коварны с кетчупом.") {}
    
protected:
    int calculateActualDamage(int damage) override {
        // КартофьФри не имеет особой защиты
        return damage;
    }
    
    int calculateActualAttack() override {
        // КартофьФри атакует дважды за ход
        std::cout << "  " << name_ << " атакует дважды! +3 и +3 жира" << std::endl;
        return 3 + 3; // Две атаки по 3
    }
};

class Mayonezius : public Mob {
private:
    float nextDamageReduction_; // 30% = 0.3
    bool hasSpecialAttack_;
    
public:
    Mayonezius()
        : Mob("Майонезиус", 18, 7,
              "Белый и коварный соус-предатель. Проникает в салаты, на бутерброды, "
              "даже в супы! Делает любую еду в 3 раза жирнее.")
        , nextDamageReduction_(0.3f)
        , hasSpecialAttack_(false) {}
    
protected:
    int calculateActualDamage(int damage) override {
        // Майонезиус снижает эффективность следующего удара
        if (hasSpecialAttack_) {
            int reducedDamage = static_cast<int>(damage * (1.0f - nextDamageReduction_));
            std::cout << "  Майонезная защита! Урон снижен на 30%: " 
                      << reducedDamage << " вместо " << damage << std::endl;
            hasSpecialAttack_ = false;
            return reducedDamage;
        }
        return damage;
    }
    
    int calculateActualAttack() override {
        // Майонезиус атакует и активирует защиту на следующий ход
        hasSpecialAttack_ = true;
        std::cout << "  " << name_ << " покрыл всё майонезом! "
                  << "Следующий урон будет слабее на 30%" << std::endl;
        return fatAttack_;
    }
    
    void onReset() override {
        hasSpecialAttack_ = false;
    }
};

class KolaSakhar : public Mob {
private:
    bool sugarAddictionApplied_;
    
public:
    KolaSakhar()
        : Mob("КолаСахар", 12, 4,
              "Шипучий провокатор. Обещает 'освежить', но на деле только добавляет "
              "пустых калорий и жажды... к ещё больше коле!")
        , sugarAddictionApplied_(false) {}
    
protected:
    int calculateActualDamage(int damage) override {
        // КолаСахар не имеет особой защиты
        return damage;
    }
    
    int calculateActualAttack() override {
        // КолаСахар атакует стабильно
        return fatAttack_;
    }
    
public:
    /**
     * @brief Вызывается при смерти моба
     * @return true, если вызвана сахарная зависимость
     */
    bool onDeath() {
        if (!sugarAddictionApplied_) {
            sugarAddictionApplied_ = true;
            std::cout << "  " << name_ << " оставил сахарную зависимость! "
                      << "Следующий моб будет атаковать сильнее" << std::endl;
            return true;
        }
        return false;
    }
    
    void onReset() override {
        sugarAddictionApplied_ = false;
    }
};

class Chipsodemon : public Mob {
public:
    Chipsodemon()
        : Mob("Чипсодемон", 22, 5,
              "Хрустящий искуситель с паприкой, солью и чувством вины. "
              "Одна пачка — и Богдан уже не может остановиться!") {}
    
protected:
    int calculateActualDamage(int damage) override {
        // Чипсодемон не имеет особой защиты
        return damage;
    }
    
    int calculateActualAttack() override {
        // Чипсодемон каждый третий ход заставляет съесть ещё чипс
        if (turnCount_ % 3 == 0 && turnCount_ > 0) {
            std::cout << "  " << name_ << " заставил съесть ещё чипс! +5 к атаке" 
                      << std::endl;
            return fatAttack_ + 5;
        }
        return fatAttack_;
    }
};

class Tortila : public Mob {
private:
    int creamShield_;
    
public:
    Tortila()
        : Mob("Тортила", 35, 12,
              "Сладкая убийца фигуры. Притворяется праздничным угощением, "
              "но её крем — чистое зло в розовой обёртке.")
        , creamShield_(10) {}
    
protected:
    int calculateActualDamage(int damage) override {
        // Тортила имеет кремовый щит
        if (creamShield_ > 0) {
            if (damage <= creamShield_) {
                creamShield_ -= damage;
                std::cout << "  Кремовый щит поглотил весь урон! "
                          << "Щит: " << creamShield_ << "/10" << std::endl;
                return 0;
            } else {
                int actualDamage = damage - creamShield_;
                std::cout << "  Кремовый щит поглотил " << creamShield_ 
                          << " урона! Осталось: " << actualDamage << std::endl;
                creamShield_ = 0;
                return actualDamage;
            }
        }
        return damage;
    }
    
    int calculateActualAttack() override {
        // Тортила атакует стабильно
        return fatAttack_;
    }
    
    void onReset() override {
        creamShield_ = 10;
    }
};

class SosiskoPredatel : public Mob {
private:
    bool shouldSplit_;
    
public:
    SosiskoPredatel()
        : Mob("СосискоПредатель", 28, 9,
              "Длинный, скользкий и коварный. Говорит, что он 'белковый' и 'диетический', "
              "но на 70% состоит из жира и сои!")
        , shouldSplit_(false) {}
    
protected:
    int calculateActualDamage(int damage) override {
        // СосискоПредатель разделяется при получении малого урона
        if (damage > 0 && damage < 5 && currentHealthPoints_ > 0) {
            shouldSplit_ = true;
            std::cout << "  " << name_ << " получил маленький урон (" << damage 
                      << ") и разделяется!" << std::endl;
            return 0; // Не наносим урон, вместо этого разделяемся
        }
        return damage;
    }
    
    int calculateActualAttack() override {
        // СосискоПредатель атакует стабильно
        return fatAttack_;
    }
    
public:
    bool shouldSplit() const { return shouldSplit_; }
    
    void onReset() override {
        shouldSplit_ = false;
    }
};

class TroynorChizburger : public Mob {
private:
    int phase_;
    bool summonedFries_;
    
public:
    TroynorChizburger()
        : Mob("ТройнорЧизбурггер", 50, 15,
              "КОРОЛЬ ВСЕГО ЖИРНОГО! Три говяжьи котлеты, шесть ломтиков сыра, "
              "бекон, двойной майонез, булочка с кунжутом и чувство глубокого сожалия. "
              "Апокалипсис в упаковке!")
        , phase_(1)
        , summonedFries_(false) {}
    
protected:
    int calculateActualDamage(int damage) override {
        // ТройнорЧизбурггер не имеет особой защиты
        return damage;
    }
    
    int calculateActualAttack() override {
        // Определяем текущую фазу
        if (currentHealthPoints_ > 35) {
            phase_ = 1;
        } else if (currentHealthPoints_ > 20) {
            phase_ = 2;
            
            // Призываем картошку-фри один раз на 2 фазе
            if (!summonedFries_) {
                summonedFries_ = true;
                std::cout << "  ТройнорЧизбурггер призывает Картошку-фри на помощь!" 
                          << std::endl;
            }
        } else {
            phase_ = 3;
        }
        
        // Рассчитываем атаку в зависимости от фазы
        int attack = fatAttack_;
        if (phase_ == 2) {
            attack += 3;
            std::cout << "  " << name_ << " (Ярость сыра) атакует на +" 
                      << attack << " жира!" << std::endl;
        } else if (phase_ == 3) {
            attack += 5;
            std::cout << "  " << name_ << " (Последний рык) атакует на +" 
                      << attack << " жира!" << std::endl;
        } else {
            std::cout << "  " << name_ << " атакует на +" 
                      << attack << " жира!" << std::endl;
        }
        
        return attack;
    }
    
    void onReset() override {
        phase_ = 1;
        summonedFries_ = false;
    }
    
public:

    int getPhase() const { return phase_; }
    
    bool hasSummonedFries() const { return summonedFries_; }
};


class MobFactory {
public:

    static std::unique_ptr<Mob> createMob(const std::string& mobType) {
        if (mobType == "pelmen") {
            return std::make_unique<Pelmen>();
        } else if (mobType == "pizzazhur") {
            return std::make_unique<PizzaZhur>();
        } else if (mobType == "burgertolstun") {
            return std::make_unique<BurgerTolstun>();
        } else if (mobType == "kartoffri") {
            return std::make_unique<KartofFri>();
        } else if (mobType == "mayonezius") {
            return std::make_unique<Mayonezius>();
        } else if (mobType == "kolasakhar") {
            return std::make_unique<KolaSakhar>();
        } else if (mobType == "chipsodemon") {
            return std::make_unique<Chipsodemon>();
        } else if (mobType == "tortila") {
            return std::make_unique<Tortila>();
        } else if (mobType == "sosiskopredatel") {
            return std::make_unique<SosiskoPredatel>();
        } else if (mobType == "troynorchizburger") {
            return std::make_unique<TroynorChizburger>();
        }
        return nullptr;
    }
    
    static std::unique_ptr<Mob> createRandomMob(bool excludeBoss = true) {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        
        std::vector<std::string> mobTypes = {
            "pelmen", "pizzazhur", "burgertolstun", 
            "kartoffri", "mayonezius", "kolasakhar",
            "chipsodemon", "tortila", "sosiskopredatel"
        };
        
        if (!excludeBoss) {
            mobTypes.push_back("troynorchizburger");
        }
        
        std::uniform_int_distribution<> dis(0, mobTypes.size() - 1);
        std::string mobType = mobTypes[dis(gen)];
        
        return createMob(mobType);
    }
    
    static std::vector<std::string> getAllMobNames() {
        return {
            "Пельмений", "ПиццеЖор", "БургероТолстун",
            "КартофьФри", "Майонезиус", "КолаСахар",
            "Чипсодемон", "Тортила", "СосискоПредатель",
            "ТройнорЧизбурггер"
        };
    }
    
    static std::unique_ptr<Mob> createMobByIndex(int index) {
        static std::vector<std::string> mobTypes = {
            "pelmen", "pizzazhur", "burgertolstun", 
            "kartoffri", "mayonezius", "kolasakhar",
            "chipsodemon", "tortila", "sosiskopredatel",
            "troynorchizburger"
        };
        
        if (index < 0 || index >= static_cast<int>(mobTypes.size())) {
            return nullptr;
        }
        
        return createMob(mobTypes[index]);
    }
};


inline void demonstrateMobs() {
    std::cout << "=== Демонстрация системы мобов ===" << std::endl;
    std::cout << std::endl;
    
    auto mob = MobFactory::createRandomMob();
    std::cout << "Создан моб: " << mob->getName() << std::endl;
    std::cout << "Описание: " << mob->getDescription() << std::endl;
    std::cout << "HP: " << mob->getHealthPoints() << "/" 
              << mob->getMaxHealthPoints() << std::endl;
    std::cout << "Базовая атака: " << mob->getFatAttack() << " жира" << std::endl;
    std::cout << "Жив: " << (mob->isAlive() ? "Да" : "Нет") << std::endl;
    
    std::cout << std::endl << "--- Демонстрация боя ---" << std::endl;
    
    int fatGain = mob->performAttack();
    std::cout << mob->getName() << " атакует! Богдан получает +" 
              << fatGain << " жира" << std::endl;
    
    mob->takeDamage(10);
    std::cout << mob->getName() << " получает 10 урона" << std::endl;
    std::cout << "Статус: " << mob->getStatus() << std::endl;
    
    mob->reset();
    std::cout << std::endl << "Сброс состояния: " << mob->getStatus() << std::endl;
    
    std::cout << std::endl << "--- Тестирование всех мобов ---" << std::endl;
    
    auto mobNames = MobFactory::getAllMobNames();
    for (size_t i = 0; i < mobNames.size(); ++i) {
        auto testMob = MobFactory::createMobByIndex(i);
        if (testMob) {
            std::cout << i+1 << ". " << testMob->getName() 
                      << " (HP: " << testMob->getMaxHealthPoints()
                      << ", Атака: " << testMob->getFatAttack() << ")" << std::endl;
        }
    }
}