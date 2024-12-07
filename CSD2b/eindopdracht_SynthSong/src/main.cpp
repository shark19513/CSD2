#include <iostream>
#include "customCallback.h"

// TODO: define SAMPLERATE globally? should probz be in highest base class

int main() {
    ScopedMessageThreadEnabler scopedMessageThreadEnabler;
    CustomCallback audioSource (44100);
    JUCEModule juceModule (audioSource);
    juceModule.init(2,2);

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