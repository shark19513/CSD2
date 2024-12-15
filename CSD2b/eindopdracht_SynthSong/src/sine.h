#ifndef SINE_H
#define SINE_H
#include <iostream>

#include "oscillator.h"

class Sine : public Oscillator
{
public:
    Sine();
    ~Sine();

protected:
    void calculate() override;
};

#endif