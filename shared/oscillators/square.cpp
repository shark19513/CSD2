#include "square.h"

Square::Square(float sampleRate, float frequency) : Oscillator(sampleRate, frequency) {
}

Square::~Square() {
}

void Square::calculateNextSample()
{
    if (m_phase < 0.5f) {
        m_sample = m_amplitude;
    } else {
        m_sample = -m_amplitude;
    }
}