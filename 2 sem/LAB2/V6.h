#ifndef V6_H
#define V6_H

#include <iostream>
#include <utility>

class Base {
    protected:
    std::pair<int,int> Point;

    public:

    Base() = default;
    Base(int x1_, int x2_) { Point = std::make_pair(x1_, x2_);}
    ~Base() = default;

    virtual void Set( int x1_, int x2_) { Point.first = x1_; Point.second = x2_;}
    virtual void Show() { std::cout << "(" << Point.first << ";" << Point.second << ")\n";}
        
};

class Inherited : public Base {
    private:

        int y;

    public:

        Inherited(int x1, int x2, int y_) : Base(x1,x2), y(y_) {}
        ~Inherited() = default;

        virtual void Set( int x1, int x2) override {
            Base::Set(x1,x2 );
            int y_;
            std::cout << "Какое число y поставить им в соответсвие?";
            std::cin >> y_;
            y = y_;
        }

        virtual void Show () override {
            std::cout << y << ":";
            Base::Show();
        }

        int Run() {
            return ((Point.first + Point.second) * y);
        }
        
};
#endif