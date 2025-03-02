#ifndef CALLBACK_H
#define CALLBACK_H

#include <audiocomponent.h>
#include "tremolo.h"
#include "delay.h"
#include "bitcrusher.h"
#include "waveshaper.h"
#include "chorus.h"
#include "filters.h"
#include "saw.h"


class CustomCallback : public AudioCallback {
public:
  CustomCallback (float sampleRate);
  void prepare(int rate) override;
  void process(AudioBuffer buffer) override;

private:
  float m_samplerate;
  Saw saw{220};
  Tremolo tremolo {6, 1};
  Delay delay {1000, static_cast<unsigned int>(m_samplerate * 2)};
  BitCrusher bitCrusher{2};
  Waveshaper waveshaper{10};
  Chorus chorus{m_samplerate, 10, 6};
  IIRFilter filter;
};

#endif //CALLBACK_H
