#include "waveshaper.h"

Waveshaper::Waveshaper(float k) : m_k(k) {
    fillBuffer();
}

Waveshaper::~Waveshaper() {}

void Waveshaper::prepare(float sampleRate) {}

void Waveshaper::applyEffect(const float &input, float &output) {
    float sample = input;

    if (sample > 0.99f) sample = 0.99f;
    if (sample < -0.99f) sample = -0.99f;

    float indexFloat = Interpolation::mapInRange(sample,
        -1.0f, 1.0f, 0.0f,
        static_cast<float>(BUFFER_SIZE - 1));

    unsigned int index = static_cast<unsigned int>(indexFloat);

    // store the part behind the decimal
    float fractionalPart = indexFloat - static_cast<float>(index);

    output = Interpolation::linMap(fractionalPart, m_buffer[index],
                                m_buffer[index + 1]);
}

void Waveshaper::setK(float k) {
    this->m_k = k;
    fillBuffer();
}

void Waveshaper::fillBuffer() {
    WavetableGenerator::generateSCurve(m_buffer,
        BUFFER_SIZE, m_k);
}
