#ifndef OSCILLATOR_H
#define OSCILLATOR_H
#include <iostream>
#include <cmath>

class Oscillator
{
public:
    // constructor/destructor
    Oscillator(float frequency, float samplerate = 44100); //TODO: add amp as argument
    ~Oscillator();

    void setSamplerate(float samplerate);

    // return current sample
    float getSample();

    // getters/setters
    void setFrequency(float frequency);
    float getFrequency();

protected:
    // calculate _frequency / _samplerate
    void updatePhaseIncrement();

    float _frequency;
    float _amplitude;
    float _phase;
    float _phaseIncrement = 0.0f;
    float _previousFrequency = -1.0f;
    // _sample contains the current sample
    float _sample;
    float _samplerate;
};

#endif