#ifndef SQUARE_H
#define SQUARE_H
#include <iostream>
#include <cmath>

#include "oscillator.h"

class Square : public Oscillator
{
public:
    Square(float frequency);
    ~Square();

    // go to next sample
    void tick();
};

#endif