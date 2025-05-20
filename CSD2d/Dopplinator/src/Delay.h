#ifndef DELAY_H
#define DELAY_H
#include <iostream>
#include <cmath>
#include "Effect.h"
#include "interpolation.h"

/* FRACTIONAL INTERPOLATING DELAY */
class Delay : public Effect {
public:
    Delay(float delayTimeMillis, float maxDelayMillis);
    virtual ~Delay() override;

    void prepare(float sampleRate) override;

    void applyEffect(const float& input, float& output) override;

    void setFeedback(float feedback);
    void setDelayTime(float delayTimeMillis);
    float getFeedback();
    float getDelayTime(); // returns TARGET delay time in ms

protected:
    float millisecondsToSamples(float millis);

    float samplesToMilliseconds(unsigned int samples);

    void setDelayTimeSamples(float delayTimeSamples);

    // increase write head and wrap if necessary
    inline void incrWriteH() {
        m_writeH++;
        wrapH(m_writeH);
    }
    inline void wrapH(unsigned int& head) {
        if (head >= m_bufferSize) head -= m_bufferSize;
    }

    void allocateBuffer();
    void releaseBuffer();

    float m_sampleRate;
    float m_delayTimeMillis; // stores delay time BEFORE interpolation
    float m_maxDelayTimeMillis;

    float m_delayTimeSamples; // current delay time (gets updated while smoothing)
    std::atomic<float> m_targetDelayTimeSamples; // to interpolate to
    std::atomic<float> m_smoothingStepSize; // calculated step size
    std::atomic<bool> m_theTimesTheyAreAChanging; // true if interpolation is currently happening

    float m_feedback;

    float* m_buffer;
    unsigned int m_bufferSize;
    unsigned int m_writeH;
};

#endif //DELAY_H
