#include "saw.h"

Saw::Saw(float frequency)
    : Oscillator(frequency) {
}

Saw::Saw(float frequency, float phase)
    : Oscillator(frequency, phase) {
}

Saw::Saw(float sampleRate, float frequency, float phase)
    : Oscillator(sampleRate, frequency, phase) {
}

Saw::~Saw() {}

void Saw::calculateNextSample() {
    m_sample = m_phase * m_amplitude;
}