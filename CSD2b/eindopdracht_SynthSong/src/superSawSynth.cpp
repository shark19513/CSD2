#include "superSawSynth.h"

SuperSawSynth::SuperSawSynth() {
    std::cout<<"SuperSawSynth - constructor\n";
    this->_numOsc = 4;
    this-> oscillators[0] = Saw{440, 1};
    this-> oscillators[1] = Saw{445, 1};
    this-> oscillators[2] = Saw{450, 1};
    this-> oscillators[3] = Saw{455, 1};
}

SuperSawSynth::~SuperSawSynth() {
  std::cout<<"SuperSawSynth - destructor\n";
}