#include "squareBassSynth.h"

SquareBassSynth::SquareBassSynth() {
    std::cout<<"SquareBassSynth - constructor\n";
}

SquareBassSynth::~SquareBassSynth() {
  std::cout<<"SquareBassSynth - destructor\n";
}


void SquareBassSynth::setOscFreqs(float frequency) {
    squareOsc.setFrequency(frequency/4); // 2 octave lower
    sineOsc.setFrequency(frequency/8); // 3 octaves lower
}

void SquareBassSynth::tickAll() {
    squareOsc.tick();
    sineOsc.tick();
    updateFrameIndex();
}

float SquareBassSynth::getSamples() {
    return (squareOsc.getSample()+sineOsc.getSample())/2;
}