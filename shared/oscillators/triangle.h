#ifndef TRIANGLE_H
#define TRIANGLE_H
#include <iostream>

#include "oscillator.h"

class Triangle : public Oscillator
{
public:
    Triangle(float frequency);
    Triangle(float sampleRate, float frequency);
    ~Triangle() override;

protected:
    void calculateNextSample() override;
};

#endif