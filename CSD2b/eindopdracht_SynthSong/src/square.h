#ifndef SQUARE_H
#define SQUARE_H
#include <iostream>

#include "oscillator.h"

class Square : public Oscillator
{
public:
    Square(float frequency);
    ~Square();

protected:
    void calculate() override;
};

#endif