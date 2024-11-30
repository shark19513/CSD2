#ifndef SINE_H
#define SINE_H
#include <iostream>
#include <cmath>

#include "oscillator.h"

class Sine : public Oscillator
{
public:
    Sine(float frequency);
    ~Sine();

    // go to next sample
    void tick();
};

#endif