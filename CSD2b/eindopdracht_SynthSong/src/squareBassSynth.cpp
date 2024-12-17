#include "squareBassSynth.h"

SquareBassSynth::SquareBassSynth(float sampleRate) : Synth(sampleRate),
                    squareOsc(sampleRate), sineOsc(sampleRate) {
    std::cout << "SquareBassSynth - constructor\n";
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

    if (bitCrusher._bypassBitCrusher == true) { //TODO: this could be more efficient
        return _samples;
    } else {
        return bitCrusher.applyBitReduction(_samples);
    }
}