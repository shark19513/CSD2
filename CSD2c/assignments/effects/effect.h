//
// Created by Semuel Leijten on 10/02/2025.
//

#ifndef EFFECT_H
#define EFFECT_H



class Effect {
public:
    Effect();
    virtual ~Effect();

    virtual void prepare(float sampleRate) = 0;
    void processFrame(const float &input, float &output);

    void setWetLevel(float wetLevel);
    void setBypassState(bool state);

protected:
    virtual void applyEffect(const float& input, float& output) = 0;

    bool m_bypassed;
    float m_wetLevel;
};



#endif //EFFECT_H
