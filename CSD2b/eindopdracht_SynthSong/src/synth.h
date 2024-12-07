#ifndef SYNTH_H
#define SYNTH_H

#include "sine.h"
#include "saw.h"
#include "square.h"

class Synth {
public:
    Synth();
    ~Synth();

    void userInterface();

    // call ticks for all oscillators
    void tickAll();

    // get samples from all oscillators
    float getSamples();

protected:
    Sine sineOsc{262};
    Saw sawOsc{330};
    Square squareOsc{392};
};

#endif