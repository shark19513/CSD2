#include <iostream>
#include "customCallback.h"
#include "synth.h"

// TODO: define SAMPLERATE globally? should probz be in highest base class

int main() {
    ScopedMessageThreadEnabler scopedMessageThreadEnabler;
    CustomCallback audioSource (44100);
    JUCEModule juceModule (audioSource);
    juceModule.init(1,1);

    Synth synth;
    std::cout << synth.sawOsc.getFrequency();

    std::cout << "Press q + Enter to quit..." << std::endl;
    bool running = true;
    while (running) {
        switch (std::cin.get()) {
            case 'q':
                running = false;
                break;
        }
    }

    return 0;
}
