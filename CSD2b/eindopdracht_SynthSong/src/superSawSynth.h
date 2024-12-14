#ifndef SUPERSAWSYNTH_H
#define	SUPERSAWSYNTH_H

#include "synth.h"

#define NUM_SAWS 5

class SuperSawSynth : public Synth {
  public:
    SuperSawSynth();
    ~SuperSawSynth();

    void tickAll(TunePlayer& tunePlayer) override;
    float getSamples() override;

  protected:
    std::array<Saw, NUM_SAWS> saws{
      Saw{430, 1},
      Saw{435, 1},
      Saw{440, 1},
      Saw{445, 1},
      Saw{450, 1}
    };
};

#endif