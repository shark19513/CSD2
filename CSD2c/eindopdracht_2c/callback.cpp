#include "callback.h"

CustomCallback::CustomCallback (float sampleRate)
  : AudioCallback (sampleRate), m_samplerate (sampleRate) {}

void CustomCallback::prepare(int rate) {
  m_samplerate = static_cast<float>(rate);
  std::cout << "\nsamplerate: " << m_samplerate << "\n";

  saw.prepare(m_samplerate);

  delay.prepare(m_samplerate);
  delay.setBypassState(false);
  delay.setWetLevel(0.3f);
  delay.setFeedback(0.25f);

  stereoChorus.prepare(m_samplerate);
  stereoChorus.setBypassState(false);

  waveshaper.setBypassState(false);

  filter.setCoefficient(0.7f);
}

void CustomCallback::process(AudioBuffer buffer) {
  auto [inputChannels, outputChannels, numInputChannels, numOutputChannels, numFrames] = buffer;
  float sample1_channel1, sample2_channel1, sample1_channel2, sample2_channel2;

  for (int i = 0u; i < numFrames; i++) {
    float inputSample = inputChannels[0][i];

    sample1_channel1 = inputSample;
    sample1_channel2 = inputSample;

    waveshaper.processFrame(sample1_channel1, sample2_channel1);
    waveshaper.processFrame(sample1_channel2, sample2_channel2);

    delay.processFrame(sample2_channel1, sample1_channel1);
    delay.processFrame(sample2_channel2, sample1_channel2);

    stereoChorus.processFrame(sample1_channel1, sample1_channel2,
                              sample2_channel1, sample2_channel2);
    filter.processFrame(sample2_channel1, sample1_channel1);
    filter.processFrame(sample2_channel2, sample1_channel2);
    outputChannels[0][i] = sample1_channel1;
    outputChannels[1][i] = sample1_channel2;
  }
}

