#ifndef SQUAREBASSSYNTH_H
#define	SQUAREBASSSYNTH_H

#include "synth.h"

#define NUM_OSC 2

class SquareBassSynth : public Synth {
  public:
    SquareBassSynth(float sampleRate);
    ~SquareBassSynth() override;

    void setOscFreqs(float frequency) override;
    void tickAll() override;
    float getSamples() override;

    protected:
      Square squareOsc;
      Sine sineOsc;
};

#endif