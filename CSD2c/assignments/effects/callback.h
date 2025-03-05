#ifndef CALLBACK_H
#define CALLBACK_H

#include <audiocomponent.h>
#include "tremolo.h"
#include "delay.h"
#include "bitcrusher.h"
#include "waveshaper.h"
#include "chorus.h"
#include "StereoChorus.h"
#include "filters.h"
#include "saw.h"


class CustomCallback : public AudioCallback {
public:
  CustomCallback (float sampleRate);
  void prepare(int rate) override;
  void process(AudioBuffer buffer) override;

  IIRFilter filter;
private:
  float m_samplerate;
  Saw saw{220};
  Tremolo tremolo {6, 1};
  Delay delay {1000, 5000};
  BitCrusher bitCrusher{2};
  Waveshaper waveshaper{10};
  Chorus chorus{0.5, 4};
  StereoChorus stereoChorus{0.8, 3};
};

#endif //CALLBACK_H
