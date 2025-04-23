#ifndef CUSTOMCALLBACK_H
#define CUSTOMCALLBACK_H

#include <audiocomponent.h>
#include "saw.h"

class CustomCallback : public AudioCallback {
public:
  explicit CustomCallback (float sampleRate);
  void prepare(int rate) override;
  void process(AudioBuffer buffer) override;

  void setEffectParameters();
  void switchBypassState();

private:
  float m_samplerate;
  bool m_bypass;

  Saw m_saw{220}; // test signal

};


#endif //CUSTOMCALLBACK_H
