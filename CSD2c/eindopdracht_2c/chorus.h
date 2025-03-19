#ifndef CHORUS_H
#define CHORUS_H
#include <iostream>
#include "delay.h"
#include <sine.h>

// based on examples from Designing Audio Effects in C++ by Will Pirkle, chapter 15

// base delay of chorus is 20ms, m_LFO modulates the delay time up to 15ms around the base delay
// so mod depth of 15 = modulation from 5ms delay to 35ms delay
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
    // mod rate is frequency of Sine, so passed directly to m_LFO and not declared here
    Sine m_LFO;
    std::atomic<float> m_modDepth;
};

#endif