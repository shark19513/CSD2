#ifndef SAW_H
#define SAW_H
#include <iostream>

#include "oscillator.h"

class Saw : public Oscillator
{
public:
    Saw();
    Saw(float freqOffset);
    ~Saw();

protected:
    void calculate() override;
};

#endif