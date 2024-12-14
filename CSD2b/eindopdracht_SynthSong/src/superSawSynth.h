#ifndef SUPERSAWSYNTH_H
#define	SUPERSAWSYNTH_H

#include "synth.h"

class SuperSawSynth : public Synth {
  public:
    SuperSawSynth();
    ~SuperSawSynth();

    void tickAll() override;
    float getSamples() override;

  protected:
    int _numSaws = 5;
    std::array<Saw, 5> saws{
      Saw{430, 1},
      Saw{435, 1},
      Saw{440, 1},
      Saw{445, 1},
      Saw{450, 1}
    };
};

#endif