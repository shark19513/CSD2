#ifndef CALLBACK_H
#define CALLBACK_H

#include <audiocomponent.h>
#include "CustomOscServer.h"
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

  void setEffectParameters();

private:
  float m_samplerate;
  std::string m_serverPort = "9008";
  float m_oscMessage;

  CustomOscServer m_oscServer;

  Saw m_saw{220};

  // effects with internal memory, thus 1 for each channel
  // chorusR modSignal has phase offset for stereo effect
  Chorus m_chorusL{7.0f, 0.4f};
  Chorus m_chorusR{7.0f, 0.4f, 0.3f};

  Delay m_delayL {100, 5000};
  Delay m_delayR {100, 5000};

  SimpleLadder m_filterL;
  SimpleLadder m_filterR;

  // memoryless effects
  Waveshaper m_waveshaper{10};
  BitCrusher m_bitCrusher{12};
};

#endif //CALLBACK_H
