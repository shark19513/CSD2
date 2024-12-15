#ifndef SQUARE_H
#define SQUARE_H
#include <iostream>

#include "oscillator.h"

class Square : public Oscillator
{
public:
    Square();
    Square(float freqOffset);
    ~Square();

protected:
    void calculate() override;
};

#endif