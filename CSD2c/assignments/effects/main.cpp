//
// Created by Semuel Leijten on 08/02/2025.
//

#include <iostream>
#include <thread>
#include <audiocomponent.h>
#include <cmath>
#include <audioToFile.h>
#include "callback.h"
#include "deltasequence.h"

#define WRITE_TO_FILE 0

int main() {
    ScopedMessageThreadEnabler scopedMessageThreadEnabler;
    CustomCallback audioSource{44100};

    JUCEModule juceModule(audioSource);
    juceModule.init(2,2);

    #if WRITE_TO_FILE
        const std::string sourcePath = SOURCE_DIR;
        AudioToFile audioToFile(sourcePath + "/output.csv");
        audioToFile.write(audioSource);
        DeltaSequence::run(audioSource.filter);

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