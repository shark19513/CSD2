#include "callback.h"

CustomCallback::CustomCallback (float sampleRate)
  : AudioCallback(sampleRate), m_samplerate(sampleRate), m_oscMessage(0) {
}

void CustomCallback::prepare(int rate) {
  m_samplerate = static_cast<float>(rate);
  std::cout << "\nsamplerate: " << m_samplerate << "\n";

  m_oscServer.init(m_serverPort);
  m_oscServer.set_callback("/breath", "f");
  m_oscServer.start();
  std::cout << "Listening on port " << m_serverPort << endl;

  m_saw.prepare(m_samplerate);

  m_delayL.prepare(m_samplerate);
  m_delayL.setWetLevel(0.3f);
  m_delayL.setFeedback(0.25f);
  
  m_delayR.prepare(m_samplerate);
  m_delayR.setWetLevel(0.3f);
  m_delayR.setFeedback(0.25f);

  m_chorusL.prepare(m_samplerate);
  m_chorusR.prepare(m_samplerate);

  m_filterL.setCoefficient(0.7f);
  m_filterR.setCoefficient(0.7f);
}

void CustomCallback::setEffectParameters() {
  //store oscMessage and constrain values to 0 - 25
  m_oscMessage = juce::jlimit(0.0f, 30.0f, m_oscServer.getOscMessage());

  m_waveshaper.setK(Interpolation::mapInRange(m_oscMessage, 0, 30, 10, 200));
  m_filterL.setCoefficient(Interpolation::mapInRange(m_oscMessage, 0, 30, 0.7, 0.2));
  m_filterR.setCoefficient(Interpolation::mapInRange(m_oscMessage, 0, 30, 0.7, 0.2));
}

void CustomCallback::process(AudioBuffer buffer) {
  auto [inputChannels, outputChannels, numInputChannels, numOutputChannels, numFrames] = buffer;
  float sample1_channelL, sample2_channelL, sample1_channelR, sample2_channelR;

  setEffectParameters();

  for (int i = 0u; i < numFrames; i++) {

    // float inputSample = inputChannels[0][i];
    float inputSample = m_saw.genNextSample();

    sample1_channelL = inputSample;
    sample1_channelR = inputSample;

    m_waveshaper.processFrame(sample1_channelL, sample2_channelL);
    m_waveshaper.processFrame(sample1_channelR, sample2_channelR);

    m_chorusL.processFrame(sample2_channelL, sample1_channelL);
    m_chorusR.processFrame(sample2_channelR, sample1_channelR);

    m_delayL.processFrame(sample1_channelL, sample2_channelL);
    m_delayR.processFrame(sample1_channelR, sample2_channelR);

    m_filterL.processFrame(sample2_channelL, sample1_channelL);
    m_filterR.processFrame(sample2_channelR, sample1_channelR);

    m_bitCrusher.processFrame(sample1_channelL, sample2_channelL);
    m_bitCrusher.processFrame(sample1_channelR, sample2_channelR);

    outputChannels[0][i] = sample2_channelL;
    outputChannels[1][i] = sample2_channelR;
  }
}
