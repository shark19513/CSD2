#include "synth.h"

Synth::Synth() {
  std::cout << "Synth - Constructor\n";
}

Synth::~Synth() {
  std::cout << "Synth - Destructor\n";
}


float Synth::applyBitReduction(float sample) {
  float stepSize = 1.0f / (1 << _bitDepth);
  return std::round(sample / stepSize) * stepSize;
}

void Synth::setBitDepth(int bitDepth) {
  this->_bitDepth = bitDepth;
  //TODO: add input check
}

void Synth::setBypassBitReduction(bool bypassBitReduction) {
  this->_bypassBitReduction = bypassBitReduction;
  //TODO: add input check
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

void Synth::updateFrameIndex() {
  if (_frameIndex >= _noteDelayFactor * SAMPLE_RATE) {
    _frameIndex = 0;
    updatePitch();
  } else {
    _frameIndex++;
  }
}
