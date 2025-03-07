#include "square.h"

Square::Square(float frequency)
    : Oscillator(frequency) {
}

Square::Square(float frequency, float phase)
    : Oscillator(frequency, phase) {
}

Square::Square(float sampleRate, float frequency, float phase)
    : Oscillator(sampleRate, frequency, phase) {
}

Square::~Square() {}

void Square::calculateNextSample()
{
    if (m_phase < 0.5f) {
        m_sample = m_amplitude;
    } else {
        m_sample = -m_amplitude;
    }
}