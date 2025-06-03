#include <iostream>
#include <thread>
#include<audiocomponent.h>
#include <audioToFile.h>
#include "CustomCallback.h"

#define WRITE_TO_FILE 0

int main() {
    ScopedMessageThreadEnabler scopedMessageThreadEnabler;
    CustomCallback audioSource{48000};

    JUCEModule juceModule(audioSource);
    juceModule.init(1,2);

    #if WRITE_TO_FILE
        const std::string sourcePath = SOURCE_DIR;
        AudioToFile audioToFile(sourcePath + "/output.csv");
        audioToFile.write(audioSource);

    #else
        std::cout << "\nPress b + Enter to bypass/unbypass..." << std::endl;
        std::cout << "Press q + Enter to quit..." << std::endl;
        bool running = true;
        while (running) {
            switch (std::cin.get()) {
                case 'b':
                    audioSource.switchBypassState();
                    break;
                case 'q':
                    std::cout << "Goodbye..." << std::endl;
                    running = false;
                    break;
            }
        }
    #endif

    return 0;
}