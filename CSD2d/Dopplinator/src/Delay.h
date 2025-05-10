#ifndef DELAY_H
#define DELAY_H
#include <iostream>
#include "Effect.h"
#include "interpolation.h"

/* INTERPOLATING DELAY */
class Delay : public Effect {
public:
    Delay(float delayTimeMillis, float maxDelayMillis);
    virtual ~Delay() override;

    void prepare(float sampleRate) override;

    void applyEffect(const float& input, float& output) override;

    void setFeedback(float feedback);
    void setDelayTime(float delayTimeMillis);
    float getFeedback();
    float getDelayTime();

protected:
    Delay(){}

    float millisecondsToSamples(float millis);

    float samplesToMilliseconds(unsigned int samples);

    void setDistanceRW(float distanceRW);

    // increase write and read heads and wrap if necessary
    inline void incrWriteH() {
        m_writeH++;
        wrapH(m_writeH);
    }

    inline void incrReadH() {
        m_readH++;
        wrapH(m_readH);
    }

    inline void wrapH(float& head) {
        if (head >= m_bufferSize) head -= m_bufferSize;
    }

    void allocateBuffer();
    void releaseBuffer();
    // fields below are floats to make interpolation possible
    float m_sampleRate;
    float m_delayTimeMillis;
    float m_maxDelayTimeMillis;
    float m_delayTimeSamples;
    float m_feedback;

    float* m_buffer;
    unsigned int m_bufferSize;
    float m_readH;
    float m_writeH;
    float m_distanceRW;
};



#endif //DELAY_H
