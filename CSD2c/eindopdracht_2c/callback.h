#ifndef CALLBACK_H
#define CALLBACK_H

#include <audiocomponent.h>
#include "delay.h"
#include "waveshaper.h"
#include "StereoChorus.h"
#include "Filters.h"
#include "saw.h"
#include "triangle.h"


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
  Waveshaper waveshaper{20};
  StereoChorus stereoChorus{4, 2};
};

#endif //CALLBACK_H
