#ifndef SQUAREBASSSYNTH_H
#define	SQUAREBASSSYNTH_H

#include "synth.h"

class SquareBassSynth : public Synth {
  public:
    SquareBassSynth();
    ~SquareBassSynth();

    void tickAll(TunePlayer& tunePlayer) override;
    float getSamples() override;

    float _frequency = 110;

    protected:
      Square squareOsc{_frequency, 0};
      Sine sineOsc{_frequency/2, 0};
};

#endif