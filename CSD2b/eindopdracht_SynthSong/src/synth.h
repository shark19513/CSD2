#ifndef SYNTH_H
#define SYNTH_H

#include "sine.h"
#include "saw.h"
#include "square.h"

class Synth {
public:
    Synth();
    ~Synth();

    // call ticks for all oscillators
    void tickAll();

    // get samples from all oscillators
    float getSamples();

    // userInterface ui;

protected:
    Sine sineOsc{262, 1};
    Saw sawOsc{330, 0};
    Square squareOsc{392, 0};
};

#endif