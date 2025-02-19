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

//TODO: figure out how to use oscillator instead of mic
int main() {
    ScopedMessageThreadEnabler scopedMessageThreadEnabler;
    CustomCallback audioSource{44100};

    JUCEModule juceModule(audioSource);
    juceModule.init(1,1);

    #if WRITE_TO_FILE
        const std::string sourcePath = SOURCE_DIR;
        AudioToFile audioToFile(sourcePath + "/output.csv");
        audioToFile.write(audioSource);

    #else
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