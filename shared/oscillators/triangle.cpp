#include "triangle.h"

Triangle::Triangle(float frequency)
    : Oscillator(frequency) {
}

Triangle::Triangle(float frequency, float phase)
    : Oscillator(frequency, phase) {
}

Triangle::Triangle(float sampleRate, float frequency, float phase)
    : Oscillator(sampleRate, frequency, phase) {
}

Triangle::~Triangle() {}

void Triangle::calculateNextSample() {
    m_sample = (4.0f * fabs(m_phase - 0.5f) - 1.0f) * m_amplitude;
}
