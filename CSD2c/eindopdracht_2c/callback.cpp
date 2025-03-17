#include "callback.h"

CustomCallback::CustomCallback (float sampleRate)
  : AudioCallback(sampleRate), m_samplerate(sampleRate) {
}

void CustomCallback::prepare(int rate) {
  m_samplerate = static_cast<float>(rate);
  std::cout << "\nsamplerate: " << m_samplerate << "\n";

  saw.prepare(m_samplerate);

  delayL.prepare(m_samplerate);
  delayL.setWetLevel(0.3f);
  delayL.setFeedback(0.25f);
  delayR.prepare(m_samplerate);
  delayR.setWetLevel(0.3f);
  delayR.setFeedback(0.25f);

  chorusL.prepare(m_samplerate);
  chorusR.prepare(m_samplerate);

  filterL.setCoefficient(0.7f);
  filterR.setCoefficient(0.7f);
}

void CustomCallback::process(AudioBuffer buffer) {
  auto [inputChannels, outputChannels, numInputChannels, numOutputChannels, numFrames] = buffer;
  float sample1_channel_L, sample2_channel_L, sample1_channel_R, sample2_channel_R;

  for (int i = 0u; i < numFrames; i++) {
    // float inputSample = inputChannels[0][i];
    float inputSample = saw.genNextSample();

    sample1_channel_L = inputSample;
    sample1_channel_R = inputSample;

    waveshaper.processFrame(sample1_channel_L, sample2_channel_L);
    waveshaper.processFrame(sample1_channel_R, sample2_channel_R);

    chorusL.processFrame(sample2_channel_L, sample1_channel_L);
    chorusR.processFrame(sample2_channel_R, sample1_channel_R);

    delayL.processFrame(sample1_channel_L, sample2_channel_L);
    delayR.processFrame(sample1_channel_R, sample2_channel_R);

    filterL.processFrame(sample2_channel_L, sample1_channel_L);
    filterR.processFrame(sample2_channel_R, sample1_channel_R);

    bitCrusher.processFrame(sample1_channel_L, sample2_channel_L);
    bitCrusher.processFrame(sample1_channel_R, sample2_channel_R);

    outputChannels[0][i] = sample2_channel_L;
    outputChannels[1][i] = sample2_channel_R;
  }
}
