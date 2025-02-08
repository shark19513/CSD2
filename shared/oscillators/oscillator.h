#ifndef OSCILLATOR_H
#define OSCILLATOR_H
#include <iostream>

class Oscillator
{
public:
    Oscillator(float sampleRate, float frequency);
    virtual ~Oscillator();

    void setSamplerate(float samplerate);

    void setFrequency(float frequency);
    float getFrequency();

    void setAmplitude(float amplitude);
    float getAmplitude();

    // generate and return next sample
    float genNextSample();

protected:
    virtual void calculateNextSample() = 0;
    // calculate _frequency/_samplerate
    void updatePhaseIncrement();

    float m_frequency;
    float m_amplitude;
    float m_phase;
    float m_phaseIncrement;
    float m_previousFrequency;
    float m_sample;
    float m_samplerate;
};

#endif