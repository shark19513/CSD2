#ifndef OSCILLATOR_H
#define OSCILLATOR_H

#include <iostream>
#include <cmath>

class Oscillator
{
public:
    // constructor/destructor
    Oscillator(float frequency, float samplerate = 44100);
    ~Oscillator();

    void setSamplerate(float samplerate);

    // return current sample
    float getSample();

    // getters/setters
    void setFrequency(float frequency);
    float getFrequency();

protected:
    // this method ensures smooth waveform continuity (according to ChatGPT)
    void updatePhaseIncrement();

    const float _pi = acos(-1); // atan(1) * 4; << don't know what this is lol
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