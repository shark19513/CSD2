#ifndef OSCILLATOR_H
#define OSCILLATOR_H
#include <iostream>

class Oscillator
{
public:
    // constructor/destructor
    Oscillator(float frequency,float amplitude, float samplerate = 44100);
    ~Oscillator();

    void setSamplerate(float samplerate);

    // return current sample
    float getSample();

    // getters/setters
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
    float _phaseIncrement = 0.0f;
    float _previousFrequency = -1.0f;
    // _sample contains the current sample
    float _sample;
    float _samplerate;
};

#endif