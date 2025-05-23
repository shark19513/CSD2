//
// Created by Semuel Leijten on 10/02/2025.
//

#ifndef EFFECT_H
#define EFFECT_H
#include <iostream>


class Effect {
public:
    Effect();
    virtual ~Effect();

    virtual void prepare(float sampleRate) = 0;
    void processFrame(const float& input, float& output);

    void setWetLevel(float wetLevel);
    void setBypassState(bool state);
    void setAmplitude(float amplitude);
    float getWetLevel();
    bool getBypassState();
    float getAmplitude();


protected:
    virtual void applyEffect(const float& input, float& output) = 0;

    bool m_bypassed;
    float m_wetLevel;
    float m_amplitude;
};



#endif //EFFECT_H
