#include "synth.h"

Synth::Synth() {
  std::cout << "Synth - Constructor\n";
}

Synth::~Synth() {
  std::cout << "Synth - Destructor\n";
}

void Synth::tickAll() {
  sineOsc.tick();
  sawOsc.tick();
  squareOsc.tick();
}

float Synth::getSamples() {
  return (sineOsc.getSample()+sawOsc.getSample()+squareOsc.getSample())/3;
}