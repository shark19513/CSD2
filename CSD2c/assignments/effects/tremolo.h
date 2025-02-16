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

    // TODO: sine and mod depth aren't init this way?
    // Tremolo(){}
};

#endif