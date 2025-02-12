#include "sine.h"
#include "math.h"

Sine::Sine(float frequency)
    : Oscillator(frequency) {
}

Sine::Sine(float sampleRate, float frequency)
    : Oscillator(sampleRate, frequency) {
}

Sine::~Sine() {}

void Sine::calculateNextSample()
{
    m_sample = sin(M_PI * 2* m_phase * m_amplitude);
}