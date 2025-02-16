#include "callback.h"

CustomCallback::CustomCallback (float sampleRate)
  : AudioCallback (sampleRate), m_samplerate (sampleRate) {}

void CustomCallback::prepare(int rate) {
    m_samplerate = static_cast<float>(rate);
    std::cout << "\nsamplerate: " << m_samplerate << "\n";
    tremolo.prepare(m_samplerate);
    delay.prepare(m_samplerate);
}

void CustomCallback::process(AudioBuffer buffer) {
  auto [inputChannels, outputChannels, numInputChannels, numOutputChannels, numFrames] = buffer;
  float sample;

  for (int channel = 0u; channel < numInputChannels; channel++) {
    for (int i = 0u; i < numFrames; i++) {
      //FIXME!!!!???
      tremolo.processFrame(inputChannels[channel][i], sample);
      delay.processFrame(sample, outputChannels[channel][i]);
    }
  }
}

