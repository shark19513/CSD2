#ifndef CALLBACK_H
#define CALLBACK_H

#include <audiocomponent.h>
#include "delay.h"
#include "waveshaper.h"
#include "BitCrusher.h"
#include "chorus.h"
#include "Filters.h"
#include "saw.h"

class CustomCallback : public AudioCallback {
public:
  CustomCallback (float sampleRate);
  void prepare(int rate) override;
  void process(AudioBuffer buffer) override;

private:
  float m_samplerate;
  Saw saw{220};

  // effects with internal memory, thus 1 for each channel
  // chorusR modSignal has phase offset for stereo effect
  Chorus chorusL{7.0f, 0.4f};
  Chorus chorusR{7.0f, 0.4f, 0.3f};

  Delay delayL {100, 5000};
  Delay delayR {100, 5000};

  SimpleLadder filterL;
  SimpleLadder filterR;

  // memoryless effects
  Waveshaper waveshaper{10};
  BitCrusher bitCrusher{12};
};

#endif //CALLBACK_H
