#include "customCallback.h"

CustomCallback::CustomCallback (double Fs) : AudioCallback(Fs) {
}

CustomCallback::~CustomCallback() {
    delete synth;
    synth = nullptr;
}

void CustomCallback::prepare(int sampleRate) {
    std::vector<std::string> options;
    int numOptions;
    std::string selection;

    // set synth type
    std::cout << "You may now choose a synthesizer" << std::endl;
    options = {"SuperSawSynth", "SquareBassSynth"};
    numOptions = options.size();
    selection = UIUtility::retrieveSelection(options.data(), numOptions);

    if (selection == "SuperSawSynth") {
        synth = new SuperSawSynth(sampleRate);
    } else {
        synth = new SquareBassSynth(sampleRate);
    }

    // set bitcrusher
    std::cout << "Apply bitcrusher?" << std::endl;
    options = {"yes", "no"};
    selection = UIUtility::retrieveSelection(options.data(), numOptions);

    if (selection == "yes") {
        synth->setBypassBitCrusher(false);
        std::cout << "Choose the bit depth" << std::endl;
        synth->setBitDepth(UIUtility::retrieveValueInRange(1, 32)); // is this weird?
    } else {
        synth->setBypassBitCrusher(true);
    }

    // set tune
    std::cout << "Select a tune to play" << std::endl;
    options = {"ArpeggioTune", "FairyTune"};
    numOptions = options.size();
    selection = UIUtility::retrieveSelection(options.data(), numOptions);
    synth->setTune(selection);
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