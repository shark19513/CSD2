#ifndef SYNTH_H
#define SYNTH_H

#include "sine.h"
#include "saw.h"
#include "square.h"

class Synth {
public:
    Synth();
    ~Synth();\

protected:
    // call ticks for all oscillators
    virtual void tickAll() = 0;

    // get samples from all oscillators
    virtual float getSamples() = 0;

    // userInterface ui;
};

#endif