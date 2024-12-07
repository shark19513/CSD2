#ifndef SAW_H
#define SAW_H
#include <iostream>

#include "oscillator.h"

class Saw : public Oscillator
{
public:
    Saw(float frequency);
    ~Saw();

protected:
    void calculate() override;
};

#endif