#include "SoundSource.h"

#ifndef OSCILLATOR_H
#define OSCILLATOR_H

class Oscillator : public SoundSource { // Oscillator is a SoundSource
    public:
    Oscillator();
    Oscillator(std::string waveform);
    Oscillator(float frequency, float amplitude, std::string waveform);
    ~Oscillator(); // destructor

    // setters/getters
    void setFrequency(float frequency);
    float getFrequency();

    void setAmplitude(float amplitude);
    float getAmplitude();

    void setWaveform(std::string waveform);
    std::string getWaveform();

    private:
    float freq;
    float amp;
};

#endif