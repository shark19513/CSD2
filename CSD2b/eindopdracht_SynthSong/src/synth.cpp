#include "synth.h"

Synth::Synth(float sampleRate) : _sampleRate(sampleRate),
      _frameIndex(0), _noteDelayFactor(0.12) {
}

Synth::~Synth() {
}


//tune playing
float Synth::mtof(float mPitch){
  return 440.0 * pow (2.0, (mPitch - 69.0f) / 12.0f);
}

void Synth::updatePitch() {
  float note = getTuneNote();
  double freq = mtof(note);
  setOscFreqs(freq);
}

float Synth::getTuneNote() {
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

void Synth::setBitDepth(float bitDepth) {
  bitCrusher.setBitDepth(bitDepth);
}

float Synth::bitCrushIfnBypassed(float samples) {
  // Daan had a good laugh about this
  if (bitCrusher.getBypassState() == true) {
    return samples;
  } else {
    return bitCrusher.applyBitReduction(samples);
  }
}