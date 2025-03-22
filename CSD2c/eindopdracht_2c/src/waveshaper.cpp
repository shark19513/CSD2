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
    // lines below are written with help of AI model
    // cast to int to get rid of fractional part
    unsigned int index = static_cast<unsigned int>(indexFloat);
    // store the fractional part
    float fractionalPart = indexFloat - static_cast<float>(index);

    output = Interpolation::linMap(fractionalPart, m_buffer[index],
                                m_buffer[index + 1]);
}

void Waveshaper::setK(float k) {
    if (k >= 0.0f && k <= 1000.0f) {
        this->m_k = k;
        fillBuffer();
    } else {
        std::cout << "- Waveshaper::setK -\n"
        << "! invalid input !\n"
        << "- please enter a value between 0.0 and 1000.0 -\n";
    }
}

float Waveshaper::getK() {
    return m_k;
}

void Waveshaper::fillBuffer() {
    WavetableGenerator::generateSCurve(m_buffer,
        BUFFER_SIZE, m_k);
}
