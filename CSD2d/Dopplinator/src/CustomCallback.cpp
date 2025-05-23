#include "CustomCallback.h"

CustomCallback::CustomCallback (float sampleRate)
  : AudioCallback(sampleRate),
    m_sampleRate(sampleRate),
    m_bypass(false),
    m_sliderValue(0.0f),
    m_prevSliderValue(-1.0f) {
}

void CustomCallback::prepare(int rate)
{
  m_sampleRate = static_cast<float>(rate);
  std::cout << "\nsamplerate: " << m_sampleRate << "\n";

  m_oscServer.init(m_serverPort);
  m_oscServer.set_callback("/slider", "f");
  m_oscServer.start();
  std::cout << "Listening on port " << m_serverPort << "\n";

  m_saw.prepare(m_sampleRate);
  m_saw.setAmplitude(0.2f);

  m_dopplerL.prepare(m_sampleRate);
  m_dopplerR.prepare(m_sampleRate);
}

void CustomCallback::setEffectParameters()
{
  m_sliderValue = m_oscServer.getOscMessage();
  // epsilon indicates the error margin
  constexpr float epsilon = 0.0001f;
  // only call if the difference is larger than epsilon
  if (std::abs(m_sliderValue - m_prevSliderValue) > epsilon) {
    m_dopplerL.setObjectPosition(m_sliderValue);
    m_dopplerR.setObjectPosition(m_sliderValue);
    m_prevSliderValue = m_sliderValue;
  }
}


void CustomCallback::switchBypassState()
{
  m_bypass = !m_bypass;
  m_dopplerL.setBypassState(m_bypass);
  m_dopplerR.setBypassState(m_bypass);
}

#define TEST_SIGNAL 1

void CustomCallback::process(AudioBuffer buffer)
{
  auto [inputChannels, outputChannels, numInputChannels, numOutputChannels, numFrames] = buffer;
  float sample1_channelL, sample2_channelL, sample1_channelR, sample2_channelR;

  setEffectParameters();

  for (int i = 0u; i < numFrames; i++) {

    #if TEST_SIGNAL
      float inputSample = m_saw.genNextSample();
    #else
      float inputSample = inputChannels[0][i];
    #endif

    sample1_channelL = inputSample;
    sample1_channelR = inputSample;

    m_dopplerL.processFrame(sample1_channelL, sample2_channelL);
    m_dopplerR.processFrame(sample1_channelR, sample2_channelR);

    outputChannels[0][i] = sample2_channelL;
    outputChannels[1][i] = sample2_channelR;
  }
}
