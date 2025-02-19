//
// Created by Semuel Leijten on 19/02/2025.
//

#include "bitcrusher.h"


BitCrusher::BitCrusher(unsigned int bitDepth) {
    setBitDepth(bitDepth);
}

BitCrusher::~BitCrusher() {}

void BitCrusher::prepare(float sampleRate) {}

void BitCrusher::applyEffect(const float &input, float &output) {
    output = std::round(input / m_stepSize) * m_stepSize;
}

void BitCrusher::setBitDepth(unsigned int bitDepth) {
    //TODO: add validation
    this->m_bitDepth = bitDepth;
    m_stepSize = 1.0f / (1 << m_bitDepth);
    std::cout << "- Bit depth set to " << m_bitDepth << " -" << std::endl;
}