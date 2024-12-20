#include "squareBassSynth.h"

SquareBassSynth::SquareBassSynth(float sampleRate) : Synth(sampleRate),
                    squareOsc(sampleRate), sineOsc(sampleRate) {
}

SquareBassSynth::~SquareBassSynth() {
}


void SquareBassSynth::setOscFreqs(float frequency) {
    // square is 2 octave lower
    squareOsc.setFrequency(frequency/4);
    // sine is 3 octaves lower
    sineOsc.setFrequency(frequency/8);
}

void SquareBassSynth::tickAll() {
    squareOsc.tick();
    sineOsc.tick();
}

float SquareBassSynth::getSamples() {
    _samples =(squareOsc.getSample()+sineOsc.getSample())/NUM_OSC;
    return bitCrushIfNotBypassed(_samples);
}