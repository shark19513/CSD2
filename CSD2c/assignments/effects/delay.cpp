//
// Created by Semuel Leijten on 10/02/2025.
//

#include "delay.h"

Delay::Delay(float delayTimeMillis, unsigned int maxDelaySamples)
    : m_bufferSize(maxDelaySamples), m_readH(0), m_writeH(0), m_feedback(0.25) {
    allocateBuffer();
    setDelayTime(delayTimeMillis);
}

Delay::~Delay() {
    releaseBuffer();
}

void Delay::prepare(float sampleRate) {
    this->m_sampleRate = sampleRate;
}

void Delay::applyEffect(const float& input, float& output) {
    output = m_buffer[m_readH];
    incrReadH();
    m_buffer[m_writeH] = input + output * m_feedback;
    incrWriteH();
}

void Delay::setFeedback(float feedback) {
    //TODO: add validation
    this->m_feedback = feedback;
}

void Delay::setDelayTime(float delayTimeMillis) {
    // TODO: add validation
    this->m_delayTimeMillis = delayTimeMillis;
    m_delayTimeSamples = millisecondsToSamples(delayTimeMillis);
    setDistanceRW(m_delayTimeSamples);
}

unsigned int Delay::millisecondsToSamples(float millis) {
    float delayTimeSamples = millis / 1000.0f * m_sampleRate;
    return static_cast<unsigned int>(delayTimeSamples);
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

