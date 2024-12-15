#include "synth.h"

Synth::Synth() {
  std::cout << "Synth - Constructor\n";
}

Synth::~Synth() {
  std::cout << "Synth - Destructor\n";
}

double Synth::mtof(float mPitch){
  return 440.0 * pow (2.0, (mPitch - 69.0f) / 12.0f);
}
