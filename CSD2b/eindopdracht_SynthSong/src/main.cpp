#include <iostream>
#include "audioToFile.h"
#include "customCallback.h"

#define WRITE_TO_FILE 0

int main () {
    std::cout << "Welcome to The Amazing Digital Synthesizer!!!!" << std::endl;
    std::cout << "loading..." << std::endl;
    ScopedMessageThreadEnabler scopedMessageThreadEnabler;
    CustomCallback audioSource (44100);

#if WRITE_TO_FILE

    AudioToFile audioToFile;
    audioToFile.write (audioSource);
#else
    bool running = true;
    while (running) {
        std::unique_ptr<JUCEModule> juceModule = std::make_unique<JUCEModule>(audioSource);
        juceModule->init (2, 2);

        std::cout << "Press q + Enter to quit..." << std::endl;
        std::cout << "Press r + Enter to restart..." << std::endl;

        bool moduleRunning = true;
        while (moduleRunning) {
            switch (std::cin.get()) {
                case 'r':
                    std::cout << "Restarting..." << std::endl;
                    moduleRunning = false;
                    break;
                case 'q':
                    std::cout << "Goodbye!!! :)" << std::endl;
                    moduleRunning = false;
                    running = false;
                    break;
            }
        }
    }
#endif
    return 0;
}