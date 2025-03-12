#include "callback.h"

CustomCallback::CustomCallback (float sampleRate)
  : AudioCallback (sampleRate), m_samplerate (sampleRate) {}

void CustomCallback::prepare(int rate) {
    m_samplerate = static_cast<float>(rate);
    std::cout << "\nsamplerate: " << m_samplerate << "\n";

    saw.prepare(m_samplerate);
    tremolo.prepare(m_samplerate);
    delay.prepare(m_samplerate);
    stereoChorus.prepare(m_samplerate);

    tremolo.setBypassState(true);
    delay.setBypassState(true);
    waveshaper.setBypassState(true);
    bitCrusher.setBypassState(true);
    stereoChorus.setWetLevel(1.5);
    stereoChorus.setBypassState(false);
    filter.setCoefficient(0.9f);
}

void CustomCallback::process(AudioBuffer buffer) {
  auto [inputChannels, outputChannels, numInputChannels, numOutputChannels, numFrames] = buffer;
  float sample1_channel1, sample2_channel1, sample1_channel2, sample2_channel2;


  for (int i = 0u; i < numFrames; i++) {
    const auto sawSample = saw.genNextSample();
    sample1_channel1 = sawSample;
    sample1_channel2 = sawSample;
    stereoChorus.processFrame(sample1_channel1, sample1_channel2,
                              sample2_channel1, sample2_channel2);
    outputChannels[0][i] = filter.process(sample2_channel1);
    // outputChannels[1][i] = sample2_channel2;
  }
}
