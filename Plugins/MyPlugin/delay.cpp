#include "delay.h"

#include <iomanip>

Delay::Delay(float delayTimeMillis, float maxDelayTimeMillis)
    : m_sampleRate(0), m_delayTimeMillis(delayTimeMillis),
      m_maxDelayTimeMillis(maxDelayTimeMillis),
      m_delayTimeSamples(0), m_feedback(0), m_buffer(nullptr), m_bufferSize(0),
      m_readH(0), m_writeH(0), m_distanceRW(0) {
    // prepare() should always be called before use
}

Delay::~Delay() {
    releaseBuffer();
}

void Delay::prepare(float sampleRate) {
    this->m_sampleRate = sampleRate;
    // init the buffer size to the max delay time and init the delay time
    m_bufferSize = millisecondsToSamples(m_maxDelayTimeMillis);
    allocateBuffer();
    setDelayTime(m_delayTimeMillis);
}

void Delay::applyEffect(const float& input, float& output) {
    output = m_buffer[m_readH];
    incrReadH();
    m_buffer[m_writeH] = input + output * m_feedback;
    incrWriteH();
}

void Delay::setFeedback(float feedback) {
    if (feedback >= 0.0f && feedback <= 1.0f) {
        this->m_feedback = feedback;
    } else {
        std::cout << "! invalid input !\n"
        << "- please enter a value between 0.0 and 1.0 -\n";
    }
}

void Delay::setDelayTime(float delayTimeMillis) {
    // check if delayTimeMillis falls in range[0 - m_bufferSize]
    if (delayTimeMillis >= 0.0f &&
        millisecondsToSamples(delayTimeMillis) < m_bufferSize) {

        this->m_delayTimeMillis = delayTimeMillis;
        m_delayTimeSamples = millisecondsToSamples(m_delayTimeMillis);
        setDistanceRW(m_delayTimeSamples);
    } else {
        std::cout << "! invalid input !\n"
        << "- please enter a value between 0.0 and "
        << samplesToMilliseconds(m_bufferSize - 1) << " -\n";
    }
}

float Delay::getFeedback() {
    return m_feedback;
}

float Delay::getDelayTime() {
    return m_delayTimeMillis;
}

unsigned int Delay::millisecondsToSamples(float millis) {
    float delayTimeSamples = millis / 1000.0f * m_sampleRate;
    return static_cast<unsigned int>(delayTimeSamples);
}

float Delay::samplesToMilliseconds(unsigned int samples) {
    return static_cast<float>(samples) / m_sampleRate * 1000.0f;
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
    distanceRW = distanceRW; //Ciska said this was necessary
    m_readH = m_writeH - distanceRW + m_bufferSize;
    wrapH(m_readH);
}

