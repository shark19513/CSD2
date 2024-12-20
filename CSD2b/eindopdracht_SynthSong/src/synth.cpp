#include "synth.h"

Synth::Synth(float sampleRate) : _sampleRate(sampleRate),
      _frameIndex(0), _noteDelayFactor(0.12f) {
}

Synth::~Synth() {
}


float Synth::mtof(float mPitch){
  return 440.0f * pow (2.0f, (mPitch - 69.0f) / 12.0f);
}

void Synth::updatePitch() {
  float note = (float)getTuneNote();
  float freq = mtof(note);
  setOscFreqs(freq);
}

int Synth::getTuneNote() {
  return tune->getNote();
}


void Synth::updateFrameIndex() {
  if (_frameIndex >= _noteDelayFactor * _sampleRate) {
    _frameIndex = 0;
    updatePitch();
  } else {
    _frameIndex++;
  }
}

void Synth::setTune(std::string tuneSelection) {
  if (tuneSelection == "ArpeggioTune") {
    tune = new ArpeggioTune;
  } else {
    tune = new FairyTune;
  }
    std::cout << "- " << tuneSelection << " selected -" << std::endl;
}


// bitcrusher
void Synth::setBitCrusherBypass(bool bypass) {
  bitCrusher.setBypassState(bypass);
}

void Synth::setBitCrusherBitDepth(float bitDepth) {
  bitCrusher.setBitDepth(bitDepth);
}

float Synth::bitCrushIfNotBypassed(float samples) {
  // Daan had a good laugh about this
  if (bitCrusher.getBypassState() == true) {
    return samples;
  } else {
    return bitCrusher.applyBitReduction(samples);
  }
}