//
// Created by Semuel Leijten on 10/02/2025.
//

#ifndef DELAY_H
#define DELAY_H
#include <iostream>
#include "effect.h"


class Delay : public Effect {
public:
    Delay(float delayTimeMillis,
            unsigned int maxDelaySamples);
    ~Delay() override;

    void prepare(float sampleRate) override;

    void applyEffect(const float &input, float &output) override;

    void setFeedback(float feedback);

    void setDelayTime(float delayTimeMillis);

private:
    Delay(){}

    unsigned int millisecondsToSamples(float millis);

    void setDistanceRW(unsigned int distanceRW);
    // increase write and readheads and wrap if necessary
    inline void incrWriteH() {
        m_writeH++;
        wrapH(m_writeH);
    }

    inline void incrReadH() {
        m_readH++;
        wrapH(m_readH);
    }

    inline void wrapH(unsigned int& head) {
        if (head >= m_bufferSize) head -= m_bufferSize;
    }

    void allocateBuffer();
    void releaseBuffer();

    float m_sampleRate;
    float m_delayTimeMillis;
    unsigned int m_delayTimeSamples;
    float m_feedback;

    float* m_buffer;
    unsigned int m_bufferSize;
    unsigned int m_readH;
    unsigned int m_writeH;
    unsigned int m_distanceRW;
};



#endif //DELAY_H
