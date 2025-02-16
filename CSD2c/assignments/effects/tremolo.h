#ifndef TREMOLO_H
#define TREMOLO_H

#include <iostream>
#include <sine.h>
#include "effect.h"

class Tremolo : public Effect {
public:
    Tremolo(float frequency, float modDepth);
    ~Tremolo() override;

    void prepare(float sampleRate) override;

    void applyEffect(const float &input, float &output) override;

    void setModFreq(float freq);

private:
    float m_modDepth;
    Sine m_sine;

    //NOTE: why does this need to be here?
    Tremolo(): m_sine(0) {
    }
};

#endif