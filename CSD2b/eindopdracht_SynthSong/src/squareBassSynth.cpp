#include "squareBassSynth.h"

SquareBassSynth::SquareBassSynth(float sampleRate) : Synth(sampleRate),
                    squareOsc(sampleRate), sineOsc(sampleRate) {
}

SquareBassSynth::~SquareBassSynth() {
}


void SquareBassSynth::setOscFreqs(float frequency) {
    squareOsc.setFrequency(frequency/4); // 2 octave lower
    sineOsc.setFrequency(frequency/8); // 3 octaves lower
}

void SquareBassSynth::tickAll() {
    squareOsc.tick();
    sineOsc.tick();
}

float SquareBassSynth::getSamples() {
    _samples =(squareOsc.getSample()+sineOsc.getSample())/2;
    return bitCrushIfnBypassed(_samples);
}