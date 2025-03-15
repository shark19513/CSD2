#include "sine.h"
#include "math.h"

Sine::Sine(float frequency)
    : Oscillator(frequency) {
}

Sine::Sine(float frequency, float phase)
    : Oscillator(frequency, phase) {
}

Sine::Sine(float sampleRate, float frequency, float phase)
    : Oscillator(sampleRate, frequency, phase) {
}

Sine::~Sine() {}

void Sine::calculateNextSample()
{
    m_sample = sin(M_PI * 2 * m_phase * m_amplitude);
}