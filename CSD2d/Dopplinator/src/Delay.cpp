#include "Delay.h"

#include <iomanip>

Delay::Delay(float delayTimeMillis, float maxDelayTimeMillis)
    : m_sampleRate(0), m_delayTimeMillis(delayTimeMillis),
      m_maxDelayTimeMillis(maxDelayTimeMillis),
      m_delayTimeSamples(0), m_feedback(0), m_buffer(nullptr), m_bufferSize(0),
      m_readH(0), m_readHFraction(0), m_writeH(0) {
    // prepare() should always be called before use
}

Delay::~Delay() {
    releaseBuffer();
}

void Delay::prepare(float sampleRate) {
    this->m_sampleRate = sampleRate;
    // init the buffer size to the max delay time and init the delay time
    m_bufferSize = static_cast<unsigned int>(millisecondsToSamples(m_maxDelayTimeMillis));
    allocateBuffer();
    setDelayTime(m_delayTimeMillis);
}

void Delay::applyEffect(const float& input, float& output) {
    /* nextIndex indicates the index of the element in the buffer that is 1 position (1 sample)
       ahead of the current one (indicated by m_readH)
     * this is the high number that we will interpolate to, m_readH indicates the low number */
    unsigned int nextIndex = m_readH + 1;
    wrapH(nextIndex); // wrap if necessary

    /* interpolate between the current buffer element and the next one with m_readHFraction as value */
    output = Interpolation::linMap(m_readHFraction, m_buffer[m_readH], m_buffer[nextIndex]);

    incrReadH(); // tick read head
    // write input to write head position together with the feedback from the output
    m_buffer[m_writeH] = input + output * m_feedback;
    incrWriteH(); // tick write head
}

void Delay::setFeedback(float feedback) {
    if (feedback >= 0.0f && feedback <= 1.0f) {
        this->m_feedback = feedback;
    } else {
        std::cout << "-- Delay::setFeedback --\n"
                  << "! invalid input !\n"
                  << "- please enter a value between 0.0 and 1.0 -\n";
    }
}

void Delay::setDelayTime(float delayTimeMillis) {
    /* delay time must be 1 sample minimum to prevent interpolation from 0 to 0 */

    float newDelayTimeSamples = millisecondsToSamples(delayTimeMillis);

    // check if delayTimeMillis falls in range[1 - m_bufferSize]
    if (newDelayTimeSamples >= 1.0f && newDelayTimeSamples < m_bufferSize) {
        this->m_delayTimeMillis = delayTimeMillis;
        m_delayTimeSamples = newDelayTimeSamples;
        setDistanceRW(m_delayTimeSamples);
    } else {
        std::cout << "-- Delay::setDelayTime -- \n"
                  << "! invalid input !\n"
                  << "- please enter a value between " << samplesToMilliseconds(1)
                  << " and " << samplesToMilliseconds(m_bufferSize - 1) << " -\n";
    }
}

float Delay::getFeedback() {
    return m_feedback;
}

float Delay::getDelayTime() {
    return m_delayTimeMillis;
}

float Delay::millisecondsToSamples(float millis) {
    float delayTimeSamples = millis / 1000.0f * m_sampleRate;
    return delayTimeSamples;
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

void Delay::setDistanceRW(float distanceRW) {
    /* readPos is a float to make subsample interpolation possible */
    float readPos = m_writeH - distanceRW + m_bufferSize;
    m_readH = static_cast<unsigned int>(readPos); //get rid of fractional part for read head
    m_readHFraction = readPos - m_readH; // store fraction separately
    wrapH(m_readH);
}

//TODO: interpolate to new read head position?

/* m_readH
 * m_targetReadH -- setDelay updates this
 * m_readHFraction -- setDelay also updates this since its smol
 *
 * set stepSize in setDelayTime
 *
 * bool that checks if target is reached
 * otherwise move read head a
 */