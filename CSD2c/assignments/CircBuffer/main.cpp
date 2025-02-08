#include <iostream>
// #include <thread>
#include <audioToFile.h>
#include <square.h>

#include "CircBuffer.h"

#define SAMPLE_RATE 44100



int main() {

    // set delay to quarter cycle
    unsigned int cycleFrameLength = 80;
    unsigned int bufferSize = 200;
    CircBuffer circBuffer(bufferSize, cycleFrameLength / 4);

    // init square osc based on cycle lengths (don't understand this quite yet)
    float freq = static_cast<float>(SAMPLE_RATE) / cycleFrameLength;
    Square square(SAMPLE_RATE, freq);

    const std::string sourcePath = SOURCE_DIR;
    WriteToFile fileWriter(sourcePath + "/output.csv", true);

    // generate 200 samples
    float squareSample = 0;
    for (unsigned int i = 0; i < 200; i++) {
        squareSample = square.genNextSample();
        circBuffer.write(squareSample);
        float outputSample = (squareSample + circBuffer.read()) * 0.5f;
        fileWriter.write(std::to_string(outputSample) + "\n");

        circBuffer.tick();
    }

    std::cout << "\n***** DONE ***** "
        << "\nWrote the sum of the a sine oscillator and a "
        << "delayed value to output.csv." << std::endl;

    return 0;
}