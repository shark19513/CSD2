#ifndef SQUARE_H
#define SQUARE_H
#include <iostream>

#include "oscillator.h"

class Square : public Oscillator
{
public:
    Square();
    ~Square();

protected:
    void calculate() override;
};

#endif