//
// Created by Semuel Leijten on 08/02/2025.
//

#include <iostream>
#include <thread>
#include <audiocomponent.h>
#include <cmath>
#include <audioToFile.h>
#include "callback.h"


#define WRITE_TO_FILE 0


int main() {
    std::cout << "loading..." << std::endl;
    std::cout << "Welcome to the Smoker's Lung" << std::endl;
    ScopedMessageThreadEnabler scopedMessageThreadEnabler;
    CustomCallback audioSource{48000};

    JUCEModule juceModule(audioSource);
    juceModule.init(1,2);

    #if WRITE_TO_FILE
        const std::string sourcePath = SOURCE_DIR;
        AudioToFile audioToFile(sourcePath + "/output.csv");
        audioToFile.write(audioSource);

    #else
        bool running = true;
        while (running) {
            std::cout << "Press q + Enter to quit..." << std::endl;
            switch (std::cin.get()) {
                case 'q':
                    running = false;
            }
        }
    #endif

    return 0;
}