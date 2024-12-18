#include "synth.h"

Synth::Synth(float sampleRate) : _sampleRate(sampleRate) {
  std::cout << "Synth - Constructor\n";
}

Synth::~Synth() {
  std::cout << "Synth - Destructor\n";
}


//tune playing
double Synth::mtof(float mPitch){
  return 440.0 * pow (2.0, (mPitch - 69.0f) / 12.0f);
}

void Synth::updatePitch() {
  float note = tune->getNote();
  double freq = mtof(note);
  std:: cout << "next note: " << note << ", has frequency " << freq << "\n";
  setOscFreqs(freq);
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
}


// bitcrusher
void Synth::setBitCrusherBypass(bool bypass) {
  bitCrusher.setBypassState(bypass);
}

void Synth::setBitDepth(float bitDepth) {
  // input is converted to float without user knowing hehe
  bitCrusher.setBitDepth(bitDepth);
  // type is now automatically converted to int but idk if that is ideal

  // if (bitDepth > 0 && bitDepth <= 32 && std::floor(bitDepth) == bitDepth) {
  //   bitCrusher._bitDepth = bitDepth;
  //   std::cout << "Bit-Depth: " << bitCrusher._bitDepth << "\n";
  // } else {
  //   std::cout << "Invalid input"
  //   << " please enter an integer between 0 and 32";
  // }
}

float Synth::bitCrushIfnBypassed(float samples) {
  // TODO: this could be more efficient but low priority
  if (bitCrusher.getBypassState() == true) {
    return samples;
  } else {
    return bitCrusher.applyBitReduction(samples);
  }
}