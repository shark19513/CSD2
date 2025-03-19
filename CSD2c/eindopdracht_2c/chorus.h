#ifndef CHORUS_H
#define CHORUS_H
#include <iostream>
#include "delay.h"
#include <sine.h>

// based on examples from Designing Audio Effects in C++ by Will Pirkle
// chapter 15
class Chorus : public Delay {
public:
    Chorus(float modDepth, float modRate);
    Chorus(float modDepth, float modRate, float modSignalPhase);
    virtual ~Chorus() override;

    void prepare(float sampleRate) override;
    void applyEffect(const float& input, float& output) override;

    void setModDepth(float modDepth);
    void setModRate(float modRate);

    float getModDepth();
    float getModRate();

private:
    // mod rate is frequency of m_sine
    Sine m_sine; // modulating signal
    std::atomic<float> m_modDepth;
};

#endif