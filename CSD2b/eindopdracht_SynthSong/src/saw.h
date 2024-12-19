#ifndef SAW_H
#define SAW_H
#include <iostream>

#include "oscillator.h"

class Saw : public Oscillator
{
public:
    Saw(float sampleRate);
    Saw(float freqOffset, float sampleRate);
    ~Saw() override;

protected:
    void calculate() override;
};

#endif