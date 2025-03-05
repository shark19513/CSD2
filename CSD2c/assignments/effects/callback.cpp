#include "callback.h"

CustomCallback::CustomCallback (float sampleRate)
  : AudioCallback (sampleRate), m_samplerate (sampleRate) {}

void CustomCallback::prepare(int rate) {
    m_samplerate = static_cast<float>(rate);
    std::cout << "\nsamplerate: " << m_samplerate << "\n";

    saw.prepare(m_samplerate);
    tremolo.prepare(m_samplerate);
    delay.prepare(m_samplerate);
    chorus.prepare(m_samplerate);
    stereoChorus.prepare(m_samplerate);

    tremolo.setBypassState(true);
    delay.setBypassState(true);
    waveshaper.setBypassState(true);
    bitCrusher.setBypassState(true);
    chorus.setBypassState(true);
    chorus.setWetLevel(0.5);
    stereoChorus.setWetLevel(0.5);
    filter.setCoefficient(0.9f);
}

void CustomCallback::process(AudioBuffer buffer) {
  auto [inputChannels, outputChannels, numInputChannels, numOutputChannels, numFrames] = buffer;
  float sample1, sample2;

  for (int channel = 0u; channel < numInputChannels; channel++) {
    for (int i = 0u; i < numFrames; i++) {
      sample1 = saw.genNextSample();
      // sample1 = inputChannels[channel][i];
      tremolo.processFrame(sample1, sample2);
      waveshaper.processFrame(sample2, sample1);
      bitCrusher.processFrame(sample1, sample2);
      chorus.processFrame(sample2, sample1);
      delay.processFrame(sample1, sample2);
      //NOTE: should filters also pass a reference?

      // outputChannels[channel][i] = filter.process(sample2);
      outputChannels[channel][i] = sample2;
    }
  }
}
