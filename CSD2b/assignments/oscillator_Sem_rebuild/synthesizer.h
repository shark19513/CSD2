#include "oscillator.h"
#include "keyboard.h"

#ifndef SYNTHESIZER_H
#define SYNTHESIZER_H

class Synthesizer{
    public:
    Synthesizer();
    ~Synthesizer();

    // Synthesizer has Oscillators
    Oscillator osc1{ "sine"};
    Oscillator osc2{"square"};
    Oscillator osc3{"saw"};

    // Synthesizer has a Keyboard
    Keyboard keyboard{24};

    void play();
};

#endif