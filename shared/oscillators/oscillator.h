#ifndef OSCILLATOR_H
#define OSCILLATOR_H
#include <iostream>

class Oscillator
{
public:
    Oscillator(float sampleRate, float frequency);
    virtual ~Oscillator();

    void setSamplerate(float samplerate);

    float getSample();

    void setFrequency(float frequency);
    float getFrequency();

    void setAmplitude(float amplitude);
    float getAmplitude();

    // go to next sample
    void tick();

protected:
    virtual void calculate() = 0;
    // calculate _frequency/_samplerate
    void updatePhaseIncrement();

    float _frequency;
    float _amplitude;
    float _phase;
    float _phaseIncrement;
    float _previousFrequency;
    float _sample;
    float _samplerate;
};

#endif