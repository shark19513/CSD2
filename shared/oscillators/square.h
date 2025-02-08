#ifndef SQUARE_H
#define SQUARE_H
#include <iostream>

#include "oscillator.h"

class Square : public Oscillator
{
public:
    Square(float sampleRate, float frequency);
    ~Square() override;

protected:
    void calculateNextSample() override;
};

#endif