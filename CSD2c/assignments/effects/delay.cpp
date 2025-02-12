//
// Created by Semuel Leijten on 10/02/2025.
//

#include "delay.h"

Delay::Delay(unsigned int numDelaySamples, unsigned int maxDelaySamples)
    : m_bufferSize(maxDelaySamples), m_readH(0), m_writeH(0) {
    allocateBuffer();
    setDistanceRW(numDelaySamples);
}

Delay::~Delay() {
    releaseBuffer();
}

void Delay::prepare(float sampleRate) {
}

void Delay::applyEffect(const float& input, float& output) {
    output = m_buffer[m_readH];
    incrReadH();
    //TODO: make feedback var instead of 0.25
    m_buffer[m_writeH] = input + output * 0.25;
    incrWriteH();
}

void Delay::allocateBuffer() {
    // allocate buffer and set all samples to 0
    m_buffer = new float[m_bufferSize];
    for (unsigned int i = 0; i < m_bufferSize; i++) {
        m_buffer[i] = 0;
    }
}

void Delay::releaseBuffer() {
    delete[] m_buffer;
    m_buffer = nullptr;
}

void Delay::setDistanceRW(unsigned int distanceRW) {
    distanceRW = distanceRW;
    m_readH = m_writeH - distanceRW + m_bufferSize;
    wrapH(m_readH);
}

// unsigned int Delay::millisecondsToSamples(unsigned int millis) {
//     unsigned int delayTimeSamples = (millis / 1000) * m_sampleRate;
//     return delayTimeSamples;
// }
