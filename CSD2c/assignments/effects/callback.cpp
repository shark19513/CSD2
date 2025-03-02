#include "callback.h"

CustomCallback::CustomCallback (float sampleRate)
  : AudioCallback (sampleRate), m_samplerate (sampleRate) {}

void CustomCallback::prepare(int rate) {
    m_samplerate = static_cast<float>(rate);
    std::cout << "\nsamplerate: " << m_samplerate << "\n";

    saw.prepare(m_samplerate);

    tremolo.prepare(m_samplerate);
    delay.prepare(m_samplerate);

    tremolo.setBypassState(true);
    delay.setBypassState(true);
    waveshaper.setBypassState(false);
    bitCrusher.setBypassState(true);
    chorus.setBypassState(true);
}

void CustomCallback::process(AudioBuffer buffer) {
  auto [inputChannels, outputChannels, numInputChannels, numOutputChannels, numFrames] = buffer;
  float sample1, sample2;

  for (int channel = 0u; channel < numInputChannels; channel++) {
    for (int i = 0u; i < numFrames; i++) {
      sample1 = saw.genNextSample();
      tremolo.processFrame(sample1, sample2);
      waveshaper.processFrame(sample2, sample1);
      bitCrusher.processFrame(sample1, sample2);
      chorus.processFrame(sample2, sample1);
      delay.processFrame(sample1, outputChannels[channel][i]);
    }
  }
}
