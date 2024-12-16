#include "synth.h"

Synth::Synth() {
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
  float note;
  if      (_tuneSelection == 1)
    {note = fairyTune.getNote();}
  else if (_tuneSelection == 2)
    {note = arpeggioTune.getNote();}
  else
    { std::cout << "No tune selected" << "\n";}

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

void Synth::setTuneselection(int tuneSelection) {
  if (tuneSelection == 1 || tuneSelection == 2) {
      this->_tuneSelection = tuneSelection;
  } else {
    std::cout << "Invalid selection "
    << "Please select either 1 or 2";
  }
}

void Synth::setBypassBitCrusher(bool bypassBitReduction) {
  this->_bypassBitCrusher = bypassBitReduction;
}