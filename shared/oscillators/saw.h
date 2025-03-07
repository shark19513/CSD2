#ifndef SAW_H
#define SAW_H
#include <iostream>

#include "oscillator.h"

class Saw : public Oscillator
{
public:
    Saw(float frequency);
    Saw(float frequency, float phase);
    Saw(float sampleRate, float frequency, float phase);
    ~Saw() override;

protected:
    void calculateNextSample() override;
};

#endif