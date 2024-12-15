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
    _samples =(squareOsc.getSample()+sineOsc.getSample())/2;
    if (bitcrusher._bypassBitReduction == true) {
        return _samples;
    } else {
        return bitcrusher.applyBitReduction(_samples);
    }
}