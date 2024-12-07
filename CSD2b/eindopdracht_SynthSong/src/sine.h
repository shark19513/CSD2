#ifndef SINE_H
#define SINE_H
#include <iostream>

#include "oscillator.h"

class Sine : public Oscillator
{
public:
    Sine(float frequency);
    ~Sine();

protected:
    void calculate() override;
};

#endif