#ifndef SQUARE_H
#define SQUARE_H
#include <iostream>
#include <cmath>

class Square
{
public:
    // constructor/destructor
    Square(float frequency, float samplerate = 44100);
    ~Square();

    void setSamplerate(float samplerate);

    // return current sample
    float getSample();
    // go to next sample
    void tick();

    // getters/setters
    void setFrequency(float frequency);
    float getFrequency();

private:
    const float _pi = acos(-1); // atan(1) * 4; << don't know what this is lol
    float _frequency;
    float _amplitude;
    float _phase;
    // _sample contains the current sample
    float _sample;
    float _samplerate;
};

#endif