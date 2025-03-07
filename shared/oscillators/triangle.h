#ifndef TRIANGLE_H
#define TRIANGLE_H
#include <iostream>

#include "oscillator.h"

class Triangle : public Oscillator
{
public:
    Triangle(float frequency);
    Triangle(float frequency, float phase);
    Triangle(float sampleRate, float frequency, float phase);
    ~Triangle() override;

protected:
    void calculateNextSample() override;
};

#endif