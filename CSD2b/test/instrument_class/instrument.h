#ifndef INSTRUMENT_H
#define INSTRUMENT_H

#include <iostream>
#include <string>

using namespace std;

class Instrument {
public:
    // default constructor
    Instrument();
    // overloaded constructor
    Instrument(string snd);

    string sound;

    void play() {
        cout << sound << endl;
    }
};

#endif