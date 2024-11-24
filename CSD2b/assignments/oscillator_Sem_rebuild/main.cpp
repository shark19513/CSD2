#include "synthesizer.h"

int main() {
    std::cout << "\nin main\n";
    Oscillator osc;

    std::cout << "Frequency of Oscillator object is: "
        << osc.getFrequency() << std::endl;

    osc.setFrequency(440);
    std::cout << "Frequency of Oscillator object is: "
        << osc.getFrequency() << std::endl;

    return 0;
}

// TODO: add synthesizer class
// TODO: add keyboard class
// TODO: add soundsource baseclass
// TODO: figure out how to make subclass with specific baseclass