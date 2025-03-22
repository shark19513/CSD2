//
// Created by Semuel Leijten on 19/02/2025.
//

#include "BitCrusher.h"


BitCrusher::BitCrusher(unsigned int bitDepth) {
    setBitDepth(bitDepth);
}

BitCrusher::~BitCrusher() {}

void BitCrusher::prepare(float sampleRate) {}

void BitCrusher::applyEffect(const float &input, float &output) {
    output = std::round(input / m_stepSize) * m_stepSize;
}

void BitCrusher::setBitDepth(unsigned int bitDepth) {
    if (bitDepth >= 1 && bitDepth <= 32) {
        this->m_bitDepth = bitDepth;
        m_stepSize = 1.0f / static_cast<float>(1 << m_bitDepth);
    } else {
        std::cout << "- BitCrusher::setBitDepth -\n"
        << "! invalid input !\n"
        << "- please enter a value between 1 and 32 -\n";
    }
}

unsigned int BitCrusher::getBitDepth() {
    return m_bitDepth;
}
