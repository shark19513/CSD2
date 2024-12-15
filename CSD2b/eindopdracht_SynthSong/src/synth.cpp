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

void Synth::updatePitch() {
  float note = tune.getNote();
  double freq = mtof(note);
  std:: cout << "next note: " << note << ", has frequency " << freq << "\n";
  setOscFreqs(freq);
}

void Synth::checkFrameIndex() {
  if (_frameIndex >= _noteDelayFactor * SAMPLE_RATE) {
    _frameIndex = 0;
    updatePitch();
  } else {
    _frameIndex++;
  }
}
