#include "saw.h"

Saw::Saw(float sampleRate, float frequency) : Oscillator(sampleRate, frequency) {
}

Saw::~Saw() {
}

void Saw::calculateNextSample() {
    m_sample = m_phase * m_amplitude;
}