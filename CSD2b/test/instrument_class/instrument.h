#ifndef INSTRUMENT_H
#define INSTRUMENT_H

#include <iostream>
#include <string>

class Instrument {
public:
    // default constructor
    Instrument();
    // overloaded constructor
    Instrument(std::string snd);

    std::string sound;

    void play() {
        std::cout << sound << std::endl;
    }
};

#endif