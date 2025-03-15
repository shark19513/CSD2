#ifndef CALLBACK_H
#define CALLBACK_H

#include <audiocomponent.h>
#include "delay.h"
#include "waveshaper.h"
#include "StereoChorus.h"
#include "filters.h"
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
  Delay delay {1000, 5000};
  Waveshaper waveshaper{10};
  StereoChorus stereoChorus{3, 2};

  Triangle triangle{10};
};

#endif //CALLBACK_H
