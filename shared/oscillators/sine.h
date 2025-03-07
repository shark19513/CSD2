#ifndef SINE_H
#define SINE_H
#include <iostream>

#include "oscillator.h"

class Sine : public Oscillator
{
public:
    Sine(float frequency);
    Sine(float frequency, float phase);
    Sine(float sampleRate, float frequency, float phase);
    ~Sine() override;

protected:
    void calculateNextSample() override;
};

#endif