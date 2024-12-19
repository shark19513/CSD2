#ifndef SQUARE_H
#define SQUARE_H
#include <iostream>

#include "oscillator.h"

class Square : public Oscillator
{
public:
    Square(float sampleRate);
    Square(float freqOffset, float sampleRate);
    ~Square() override;

protected:
    void calculate() override;
};

#endif