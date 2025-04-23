#include "CustomCallback.h"

CustomCallback::CustomCallback (float sampleRate)
  : AudioCallback(sampleRate),
    m_samplerate(sampleRate),
    m_bypass(false)
{
}

void CustomCallback::prepare(int rate)
{
  m_samplerate = static_cast<float>(rate);
  std::cout << "\nsamplerate: " << m_samplerate << "\n";

  m_saw.prepare(m_samplerate);
}

void CustomCallback::setEffectParameters()
{
}

void CustomCallback::switchBypassState()
{
  m_bypass = !m_bypass;
  // put method that bypasses effect here
}

void CustomCallback::process(AudioBuffer buffer)
{
  auto [inputChannels, outputChannels, numInputChannels, numOutputChannels, numFrames] = buffer;
  float sample1_channelL, sample2_channelL, sample1_channelR, sample2_channelR;

//  setEffectParameters();

  for (int i = 0u; i < numFrames; i++) {

    float inputSample = m_saw.genNextSample(); // test signal
//    float inputSample = inputChannels[0][i];

    sample1_channelL = inputSample;
    sample1_channelR = inputSample;

    outputChannels[0][i] = sample1_channelL;
    outputChannels[1][i] = sample1_channelR;
  }
}
