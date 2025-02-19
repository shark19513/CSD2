#ifndef WAVESHAPER_H_
#define WAVESHAPER_H_

#include <iostream>
#include "effect.h"
#include "wavetableGenerator.h"
#include "math.h"

#define BUFFER_SIZE 512

class Waveshaper : public Effect {
 public:
    Waveshaper(float k);
    ~Waveshaper() override;

    void prepare(float sampleRate) override;

    void applyEffect(const float &input, float &output) override;

    void setK(float k);

    void fillBuffer();

private:
    Waveshaper() {};

    inline void wrapIndex(unsigned int& index) {
        //TODO: duplicate code, this also happens in the delay
        if (index >= BUFFER_SIZE) index -= BUFFER_SIZE;
    }

    float m_k; // this is k
    float m_buffer[BUFFER_SIZE];
};


#endif
