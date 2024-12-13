#include "customCallback.h"

CustomCallback::CustomCallback (double Fs) : AudioCallback(Fs) {
}

CustomCallback::~CustomCallback() {
    delete synth;
    synth = nullptr;
}

void CustomCallback::prepare(int sampleRate) {
    initSynthType(sampleRate);
    initBitCrusher();
    initTune();
}

void CustomCallback::process (AudioBuffer buffer) {
    auto [inputChannels, outputChannels, numInputChannels, numOutputChannels, numFrames] = buffer;

    for (int sample = 0u; sample < numFrames; ++sample) {
        synth->tickAll();
        for (int channel = 0u; channel < numOutputChannels; ++channel) {
            outputChannels[channel][sample] = synth->getSamples();
        }
    }
}


void CustomCallback::initSynthType(float sampleRate) {
        std::cout << "You may now choose a synthesizer" << std::endl;
    _options = {"SuperSawSynth", "SquareBassSynth"};
    _numOptions = _options.size();
    _selection = UIUtility::retrieveSelection(_options.data(), _numOptions);

    if (_selection == "SuperSawSynth") {
        synth = new SuperSawSynth(sampleRate);
    } else {
        synth = new SquareBassSynth(sampleRate);
    }
}

void CustomCallback::initBitCrusher() {
        std::cout << "Apply bitcrusher?" << std::endl;
    _options = {"yes", "no"};
    _selection = UIUtility::retrieveSelection(_options.data(), _numOptions);

    if (_selection == "yes") {
        synth->setBitCrusherBypass(false);
        std::cout << "Choose the bit depth" << std::endl;
        synth->setBitDepth(UIUtility::retrieveValueInRange(1, 32)); // is this weird?
    } else {
        synth->setBitCrusherBypass(true);
    }
}

void CustomCallback::initTune() {
    std::cout << "Select a tune to play" << std::endl;
    _options = {"ArpeggioTune", "FairyTune"};
    _numOptions = _options.size();
    _selection = UIUtility::retrieveSelection(_options.data(), _numOptions);
    synth->setTune(_selection);
}

