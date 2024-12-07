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

    Sine sineOsc{262};
    Saw sawOsc{330};
    Square squareOsc{392};
};

#endif