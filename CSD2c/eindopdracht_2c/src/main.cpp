/*
 *                              THE SMOKER'S LUNG
 *                      Created by Semuel Leijten for CSD2C
 *                                     2025
 *
 *  Program that does processing on an audio signal with various effects some of which
 *  are controlled with OSC data from a respiration belt.
 *
 *  To use:
 *  1.  Turn on respiration belt
 *  2.  Run the program Vernier-GoDirect-RespirationBelt_bluetooth.py
 *  3a. Enter the device number in the terminal
 *   b. If the program says "open device 0 = False"
 *      - Terminate program
 *      - Shortly press on/off button on respiration belt to reconnect bluetooth
 *      - Run program again
 *  4.  Run this program
*/

#include <iostream>
#include <thread>
#include <audiocomponent.h>
#include <cmath>
#include <audioToFile.h>
#include "callback.h"


#define WRITE_TO_FILE 0


int main() {
    std::cout << "Welcome to The Smoker's Lung" << std::endl;
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