#include "waveshaper.h"

Waveshaper::Waveshaper() : m_slope(8) {
}

Waveshaper::~Waveshaper() {}

void Waveshaper::prepare(float sampleRate) {}

void Waveshaper::applyEffect(const float &input, float &output) {
    output = (1/std::atan(m_slope) * std::atan(m_slope * input));
}

void Waveshaper::setSlope(float slope) {
    this->m_slope = slope;
}