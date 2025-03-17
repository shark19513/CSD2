#ifndef WAVESHAPER_H_
#define WAVESHAPER_H_

#include <iostream>
#include "effect.h"
#include "wavetableGenerator.h"
#include "math.h"

#define BUFFER_SIZE 512

// BASED ON EXAMPLE FROM CLASS
class Waveshaper : public Effect {
public:
    Waveshaper(float k);
    ~Waveshaper() override;

    void prepare(float sampleRate) override;

    void applyEffect(const float &input, float &output) override;

    void setK(float k);
    float getK();

    void fillBuffer();

private:
    Waveshaper() {}

    float m_k; // k sets the slope of the waveshaper
    float m_buffer[BUFFER_SIZE];
};


#endif
