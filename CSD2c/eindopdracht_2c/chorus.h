#ifndef CHORUS_H
#define CHORUS_H
#include <iostream>
#include "delay.h"
#include <sine.h>


class Chorus : public Delay {
public:
    Chorus(float modDepth, float modRate);
    Chorus(float modDepth, float modRate, float modSignalPhase);
    virtual ~Chorus() override;

    void prepare(float sampleRate) override;
    void applyEffect(const float& input, float& output) override;
    void setModDepth(float modDepth) override;
    void setModRate(float modRate) override;

private:
    Sine m_sine;
    float m_modDepth;
};

#endif