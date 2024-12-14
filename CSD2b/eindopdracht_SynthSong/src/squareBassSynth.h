#ifndef SQUAREBASSSYNTH_H
#define	SQUAREBASSSYNTH_H

#include "synth.h"

class SquareBassSynth : public Synth {
  public:
    SquareBassSynth();
    ~SquareBassSynth();

    void tickAll() override;
    float getSamples() override;

    float _frequency = 110;

    protected:
      Square squareOsc{_frequency, 1};
      Sine sineOsc{_frequency/2, 1};
};

#endif