#include "squareBassSynth.h"

SquareBassSynth::SquareBassSynth() {
    std::cout<<"SquareBassSynth - constructor\n";
}

SquareBassSynth::~SquareBassSynth() {
  std::cout<<"SquareBassSynth - destructor\n";
}

void SquareBassSynth::tickAll() {
    squareOsc.tick();
    sineOsc.tick();
}

float SquareBassSynth::getSamples() {
    return (squareOsc.getSample()+sineOsc.getSample())/2;
}