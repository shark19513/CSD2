#include <iostream>
#include "audioToFile.h"
#include "customCallback.h"

// TODO: define SAMPLERATE globally? should probz be in highest base class

#define WRITE_TO_FILE 1

int main () {
    ScopedMessageThreadEnabler scopedMessageThreadEnabler;
    CustomCallback audioSource (44100);

#if WRITE_TO_FILE
    AudioToFile audioToFile;
    audioToFile.write (audioSource);
#else

    JUCEModule juceModule (audioSource);
    juceModule.init (2, 2);

    std::cout << "Press q + Enter to quit..." << std::endl;
    bool running = true;
    while (running) {
        switch (std::cin.get()) {
            case 'q':
                running = false;
        }
    }
#endif
    return 0;
}