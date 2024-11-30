#ifndef SAW_H
#define SAW_H
#include <iostream>
#include <cmath>

#include "oscillator.h"

class Saw : public Oscillator
{
public:
    Saw(float frequency);
    ~Saw();

    // go to next sample
    void tick();
};

#endif