#include "synth.h"

Synth::Synth() {
  std::cout << "Synth - Constructor\n";
}

Synth::~Synth() {
  std::cout << "Synth - Destructor\n";
}

void Synth::setSynthFrequency(double frequency) {
  this->_synthFrequency = frequency;
}