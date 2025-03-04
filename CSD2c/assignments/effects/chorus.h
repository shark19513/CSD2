#ifndef CHORUS_H
#define CHORUS_H
#include <iostream>
#include "delay.h"
#include <triangle.h>


class Chorus : public Delay {
public:
    Chorus(float modDepth, float modRate);
    virtual ~Chorus() override;

    void prepare(float sampleRate) override;
    void applyEffect(const float& input, float& output) override;
    void setModDepth(float modDepth);

private:
    Triangle m_triangle;
    float m_modDepth;
};

#endif