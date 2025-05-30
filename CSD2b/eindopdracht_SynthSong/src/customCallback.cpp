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
        synth->updateFrameIndex();
        for (int channel = 0u; channel < numOutputChannels; ++channel) {
            outputChannels[channel][sample] = synth->getSamples();
        }
    }
}


void CustomCallback::initSynthType(float sampleRate) {
    std::cout << "You may now choose a synthesizer" << std::endl;
    _options = {"SuperSawSynth", "SquareBassSynth"};
    _numOptions = (int)_options.size();
    _selection = UIUtility::retrieveSelection(_options.data(), _numOptions);

    if (_selection == "SuperSawSynth") {
        std::cout << "- " << _selection << " selected -" << std::endl;

        std::cout << "Choose the level of detuneness." << std::endl;
        _minSetting = 1.0f;
        _maxSetting = 5.0f;

        float detune = UIUtility::retrieveValueInRange(_minSetting, _maxSetting);
        std::cout << "- Detuneness set to level " << detune << " -" << std::endl;
        synth = new SuperSawSynth(sampleRate, detune);
    } else {
        std::cout << "- " << _selection << " selected -" << std::endl;
        synth = new SquareBassSynth(sampleRate);
    }
}

void CustomCallback::initBitCrusher() {
    std::cout << "Apply bitcrusher?" << std::endl;
    _options = {"yes", "no"};
    _selection = UIUtility::retrieveSelection(_options.data(), _numOptions);
    _minSetting = 1.0f;
    _maxSetting = 16.0f;

    if (_selection == "yes") {
        synth->setBitCrusherBypass(false);
        std::cout << "Choose the bit depth." << std::endl;
        synth->setBitCrusherBitDepth(UIUtility::retrieveValueInRange(_minSetting, _maxSetting));
        // bit depth is casted to int in setBitDepth() inside BitCrusher
    } else {
        synth->setBitCrusherBypass(true);
    }
}

void CustomCallback::initTune() {
    std::cout << "Select a tune to play." << std::endl;
    _options = {"ArpeggioTune", "FairyTune"};
    _numOptions = (int)_options.size();

    _selection = UIUtility::retrieveSelection(_options.data(), _numOptions);
    synth->setTune(_selection);
    // osc freqs are initialized to first note in tune
    synth->setOscFreqs(synth->mtof(synth->getTuneNote()));
}