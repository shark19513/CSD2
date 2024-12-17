#include "customCallback.h"

CustomCallback::CustomCallback (double Fs) : AudioCallback(Fs) {
}

CustomCallback::~CustomCallback() {
    delete synth;
    synth = nullptr;
}

void CustomCallback::prepare(int sampleRate) {
    // set synth type
    std::cout << "You may now choose a synthesizer" << std::endl;
    std::string synthOptions[] = {"SuperSawSynth", "SquareBassSynth"};
    int numSynthOptions = sizeof(synthOptions) / sizeof(std::string);
    std::string synthSelection = UIUtility::retrieveSelection(synthOptions, numSynthOptions);

    if (synthSelection == "SuperSawSynth") {
        synth = new SuperSawSynth(sampleRate);
    } else if (synthSelection == "SquareBassSynth") {
        synth = new SquareBassSynth(sampleRate);
    } else {
        std::cout << "No synth selected";
    }


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