#ifndef CALLBACK_H
#define CALLBACK_H

#include <audiocomponent.h>
#include "delay.h"
#include "waveshaper.h"
#include "StereoChorus.h"
#include "Filters.h"
#include "saw.h"


class CustomCallback : public AudioCallback {
public:
  CustomCallback (float sampleRate);
  void prepare(int rate) override;
  void process(AudioBuffer buffer) override;

  SimpleLadder filter;
private:
  float m_samplerate;
  Saw saw{220};
  Delay delay {500, 5000};
  Waveshaper waveshaper{10};
  StereoChorus stereoChorus{7.0f, 0.4f};
};

#endif //CALLBACK_H
