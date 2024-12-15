#ifndef SQUAREBASSSYNTH_H
#define	SQUAREBASSSYNTH_H

#include "synth.h"

class SquareBassSynth : public Synth {
  public:
    SquareBassSynth();
    ~SquareBassSynth();

    void setOscFreqs(float frequency) override;
    void tickAll() override;
    float getSamples() override;

    protected:
      Square squareOsc{};
      Sine sineOsc{};
};

#endif