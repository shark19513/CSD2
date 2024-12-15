#include "tune.h"

Tune::Tune() {
}

Tune::~Tune() {
}


float Tune::getNote() {
    // wrap index back to the beginning
    if(_index >= NUM_NOTES) {
        _index = 0;
    }
    return _melody[_index++];
}