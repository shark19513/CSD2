#include "SoundSource.h"

#ifndef OSCILLATOR_H
#define OSCILLATOR_H

class Oscillator : public SoundSource { // Oscillator is a SoundSource
    public:
    Oscillator();
    Oscillator(float frequency, float amplitude, std::string waveform);
    ~Oscillator(); // destructor

    // setters/getters
    void setFrequency(float frequency);
    float getFrequency();

    private:
    float freq;
    float amp;
};

#endif