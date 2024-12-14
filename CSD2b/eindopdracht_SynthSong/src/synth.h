#ifndef SYNTH_H
#define SYNTH_H

#include "sine.h"
#include "saw.h"
#include "square.h"
#include "tunePlayer.h"

class Synth {
public:
    Synth();
    ~Synth();

    void setSynthFrequency(double frequency);

    float _synthFrequency;

protected:
    // call ticks for all oscillators
    virtual void tickAll(TunePlayer& tunePlayer) = 0;

    // get samples from all oscillators
    virtual float getSamples() = 0;

    // userInterface ui;

    TunePlayer player{};
};

#endif