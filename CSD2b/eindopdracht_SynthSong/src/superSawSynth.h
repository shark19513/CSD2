#ifndef SUPERSAWSYNTH_H
#define	SUPERSAWSYNTH_H

#include "synth.h"

#define NUM_SAWS 5

class SuperSawSynth : public Synth {
  public:
    SuperSawSynth();
    ~SuperSawSynth();

    void setOscFreqs(float frequency) override;
    void tickAll() override;
    float getSamples() override;

  protected:
    std::array<Saw, NUM_SAWS> saws{
      Saw{},
      Saw{},
      Saw{},
      Saw{},
      Saw{}
    };
};

#endif