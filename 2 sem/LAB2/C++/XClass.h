#ifndef XCLASS_H
#define XCLASS_H

#include <iostream>

class X {
protected:
    int x1, x2;
public:
    X(int a, int b);
    virtual ~X();
    virtual void show() const;
    virtual void set(int a, int b);
    virtual int run() const;
};

class Y : public X {
    int y;
public:
    Y(int a, int b, int c);
    virtual ~Y();                           
    virtual void show() const override;          
    virtual void set(int a, int b) override;      
    void setY(int newY);                         
    int run() const override;                               
};

#endif