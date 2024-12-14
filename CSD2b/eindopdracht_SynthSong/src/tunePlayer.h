#ifndef TUNEPLAYER_H
#define TUNEPLAYER_H

#include <iostream>

#include "tune.h"
#include "synth.h"

class TunePlayer {
public:
    TunePlayer();
    ~TunePlayer();

    double mtof(float mPitch);
    void updatePitch(Tune& tune, Synth& synth);

  int _frameIndex;
  double _noteDelayFactor;

  Tune tune;
};

#endif