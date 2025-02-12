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


protected:
    virtual void applyEffect(const float& input, float& output) = 0;
};



#endif //EFFECT_H
