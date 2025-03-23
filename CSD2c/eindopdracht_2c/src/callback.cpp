#include "callback.h"

CustomCallback::CustomCallback (float sampleRate)
  : AudioCallback(sampleRate),
    m_samplerate(sampleRate),
    m_bypass(false),
    m_stepSize(0.05f),
    m_oscLowerLimit(1),
    m_oscUpperLimit(40),
    m_oscMessage(0),
    m_serverPort("9008") {
}

void CustomCallback::prepare(int rate) {
  m_samplerate = static_cast<float>(rate);
  std::cout << "\nsamplerate: " << m_samplerate << "\n";

  m_oscServer.init(m_serverPort);
  m_oscServer.set_callback("/breath", "f");
  m_oscServer.start();
  std::cout << "Listening on port " << m_serverPort << "\n";

  m_saw.prepare(m_samplerate);

  m_waveshaper.setBypassState(false);

  m_delayL.prepare(m_samplerate);
  m_delayL.setWetLevel(0.3f);
  m_delayL.setFeedback(0.25f);
  
  m_delayR.prepare(m_samplerate);
  m_delayR.setWetLevel(0.3f);
  m_delayR.setFeedback(0.25f);

  m_chorusL.prepare(m_samplerate);
  m_chorusR.prepare(m_samplerate);

  m_filterL.setCoefficient(1);
  m_filterR.setCoefficient(1);
  m_filterL.setBypassState(false);
  m_filterR.setBypassState(false);
}

void CustomCallback::setEffectParameters() {
  // osc message is received from m_oscServer
  float targetOscMessage = m_oscServer.getOscMessage();

  // values are constrained between 1.0 - 40.0
  // interpolation takes place to smoothen out the changing of the effects
  // necessary because the respiration belt has a slight time interval between messages send
  m_oscMessage = juce::jlimit(m_oscLowerLimit, m_oscUpperLimit,
    Interpolation::linMap(m_stepSize, m_oscMessage, targetOscMessage));

  // use m_oscMessage to set effect parameters
  m_waveshaper.setK(Interpolation::mapInRange(m_oscMessage, m_oscLowerLimit, m_oscUpperLimit,
                                              400, 40));
  m_filterL.setCoefficient(Interpolation::mapInRange(m_oscMessage, m_oscLowerLimit, m_oscUpperLimit,
                                              0.99f, 0.4f));
  m_filterR.setCoefficient(Interpolation::mapInRange(m_oscMessage, m_oscLowerLimit, m_oscUpperLimit,
                                              0.99f, 0.4f));
  m_chorusL.setModDepth(Interpolation::mapInRange(m_oscMessage, m_oscLowerLimit, m_oscUpperLimit,
                                              5, 10));
  m_chorusR.setModDepth(Interpolation::mapInRange(m_oscMessage, m_oscLowerLimit, m_oscUpperLimit,
                                              5, 10));
}

void CustomCallback::switchBypassState() {
  if (m_bypass) {
    m_bypass = false;
  } else {
    m_bypass = true;
  }
  m_waveshaper.setBypassState(m_bypass);
  m_chorusL.setBypassState(m_bypass);
  m_chorusR.setBypassState(m_bypass);
  m_delayL.setBypassState(m_bypass);
  m_delayR.setBypassState(m_bypass);
  m_filterL.setBypassState(m_bypass);
  m_filterR.setBypassState(m_bypass);
  m_bitCrusher.setBypassState(m_bypass);
}

void CustomCallback::process(AudioBuffer buffer) {
  auto [inputChannels, outputChannels, numInputChannels, numOutputChannels, numFrames] = buffer;
  float sample1_channelL, sample2_channelL, sample1_channelR, sample2_channelR;

  setEffectParameters();

  for (int i = 0u; i < numFrames; i++) {

    // float inputSample = m_saw.genNextSample(); // test signal
    float inputSample = inputChannels[0][i];

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
