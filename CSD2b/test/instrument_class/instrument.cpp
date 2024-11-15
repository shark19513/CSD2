#include "instrument.h"
#include <iostream>

// default constructor
Instrument::Instrument() {
    std::cout << "Instrument - default constructor\n";

    sound = "silence";
}

// overloaded constructor
Instrument::Instrument(std::string snd) {
    std::cout << "Instrument - overloaded constructor\n";

    sound = snd;
}