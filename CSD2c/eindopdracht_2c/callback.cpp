#include "callback.h"

CustomCallback::CustomCallback (float sampleRate)
  : AudioCallback (sampleRate), m_samplerate (sampleRate) {}

void CustomCallback::prepare(int rate) {
    m_samplerate = static_cast<float>(rate);
    std::cout << "\nsamplerate: " << m_samplerate << "\n";

    saw.prepare(m_samplerate);
    triangle.prepare(m_samplerate);
    delay.prepare(m_samplerate);
    stereoChorus.prepare(m_samplerate);

    delay.setBypassState(true);
    waveshaper.setBypassState(true);
    stereoChorus.setWetLevel(0.5);
    stereoChorus.setBypassState(false);
    filter.setCoefficient(0.7f);
}

void CustomCallback::process(AudioBuffer buffer) {
  auto [inputChannels, outputChannels, numInputChannels, numOutputChannels, numFrames] = buffer;
  float sample1_channel1, sample2_channel1, sample1_channel2, sample2_channel2;


  for (int i = 0u; i < numFrames; i++) {
    const auto oscSample = saw.genNextSample();

    // outputChannels[0][i] = oscSample;

    sample1_channel1 = oscSample;
    sample1_channel2 = oscSample;
    stereoChorus.processFrame(sample1_channel1, sample1_channel2,
                              sample2_channel1, sample2_channel2);
    filter.processFrame(sample2_channel1, sample1_channel1);
    filter.processFrame(sample2_channel2, sample1_channel2);
    outputChannels[0][i] = sample1_channel1;
    outputChannels[1][i] = sample1_channel2;
  }
}
