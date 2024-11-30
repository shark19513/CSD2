#ifndef SYNTH_H
#define SYNTH_H

#include "sine.h"
#include "saw.h"
#include "square.h"

class Synth {
  public:
    Synth();
    ~Synth();

    Sine sineOsc{440};
    Saw sawOsc{440};
    Square squareOsc{440};
};

#endif