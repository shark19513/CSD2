#include <iostream>
#include <thread>
#include <audioToFile.h>
#include <square.h>
#include "CircBuffer.h"

#define SAMPLE_RATE 44100

int main() {

    // set delay to quarter cycle
    int cycleFrameLength = 80;
    unsigned int bufferSize = 200;
    CircBuffer circBuffer(bufferSize, cycleFrameLength / 4);

    // init square osc based on cycle lengths (don't understand this quite yet)
    float freq = static_cast<float>(SAMPLE_RATE) / cycleFrameLength;
    Square square(SAMPLE_RATE, freq);

    const std::string sourcePath = SOURCE_DIR;
    WriteToFile writeToFile(sourcePath + "/output.csv", true);

    // generate 200 samples
    float squareSample = 0;
    for (unsigned int i = 0; i < 200; i++) {
        // TODO: remake oscillators with genNextSample()
    }

    return 0;
}