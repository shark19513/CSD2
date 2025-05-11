#ifndef CUSTOMCALLBACK_H
#define CUSTOMCALLBACK_H

#include <audiocomponent.h>
#include "CustomOscServer.h"
#include "saw.h"
#include "Delay.h"

class CustomCallback : public AudioCallback {
public:
  explicit CustomCallback (float sampleRate);
  void prepare(int rate) override;
  void process(AudioBuffer buffer) override;

  void setEffectParameters();
  void switchBypassState();

private:
  float m_sampleRate;
  bool m_bypass;

  CustomOscServer m_oscServer;
  std::string m_serverPort = "9008";

  float m_sliderValue;
  float m_prevSliderValue;

  Saw m_saw{220}; // test signal

  Delay m_delayL{1.0f, 1000.0f};
  Delay m_delayR{1.0f, 1000.0f};
};


#endif //CUSTOMCALLBACK_H
