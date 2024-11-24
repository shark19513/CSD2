#include "oscillator.h"

#ifndef SYNTHESIZER_H
#define SYNTHESIZER_H

class Synthesizer{
    public:
    Synthesizer();
    ~Synthesizer();

    Oscillator osc1{220, 0, "sine"};
    Oscillator osc2{440, 0.5, "square"};
    Oscillator osc3{880, 1, "saw"};

    void play();
};

#endif