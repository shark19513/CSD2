#include "tunePlayer.h"

TunePlayer::TunePlayer() : _frameIndex(0), _noteDelayFactor(0.1){
    std::cout<<"TunePlayer - constructor\n";
}

TunePlayer::~TunePlayer() {
  std::cout<<"TunePlayer - destructor\n";
}


double TunePlayer::mtof(float mPitch){
  return 440.0 * pow (2.0, (mPitch - 69.0f) / 12.0f);
}

void TunePlayer::updatePitch(Tune& tune, Synth& synth) {
  float note = tune.getNote();
  double freq = mtof(note);
  std:: cout << "next note: " << note << ", has frequency " << freq << "\n";
  synth.setSynthFrequency(freq);
}