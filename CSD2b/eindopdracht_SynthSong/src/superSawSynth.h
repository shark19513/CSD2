#ifndef SUPERSAWSYNTH_H
#define	SUPERSAWSYNTH_H

#include "synth.h"

#define NUM_SAWS 5

class SuperSawSynth : public Synth {
  public:
    SuperSawSynth(float sampleRate);
    ~SuperSawSynth() override;

    void setOscFreqs(float frequency) override;
    void tickAll() override;
    float getSamples() override;

  protected:
    std::vector<Saw> saws;
};

#endif