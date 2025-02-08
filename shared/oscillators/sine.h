#ifndef SINE_H
#define SINE_H
#include <iostream>

#include "oscillator.h"

class Sine : public Oscillator
{
public:
    Sine(float sampleRate, float frequency);
    ~Sine() override;

protected:
    void calculateNextSample() override;
};

#endif