#ifndef SQUARE_H
#define SQUARE_H
#include <iostream>

#include "oscillator.h"

class Square : public Oscillator
{
public:
    Square(float frequency);
    Square(float frequency, float phase);
    Square(float sampleRate, float frequency, float phase);
    ~Square() override;

protected:
    void calculateNextSample() override;
};

#endif