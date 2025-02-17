#ifndef WAVESHAPER_H_
#define WAVESHAPER_H_

#include <iostream>
#include "effect.h"
#include "math.h"

class Waveshaper : public Effect {
 public:
    Waveshaper();
    ~Waveshaper() override;

    void prepare(float sampleRate) override;

    void applyEffect(const float &input, float &output) override;

    void setSlope(float slope);

private:
    float m_slope;
};


#endif
