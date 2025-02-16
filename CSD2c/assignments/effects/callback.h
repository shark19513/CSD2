#ifndef CALLBACK_H
#define CALLBACK_H

#include <audiocomponent.h>
#include "tremolo.h"
#include "delay.h"


class CustomCallback : public AudioCallback {
public:
  CustomCallback (float sampleRate);
  void prepare(int rate) override;
  void process(AudioBuffer buffer) override;

private:
  unsigned int m_samplerate;
  Tremolo tremolo {6, 1};
  Delay delay {1000, m_samplerate * 2};
};

#endif //CALLBACK_H
