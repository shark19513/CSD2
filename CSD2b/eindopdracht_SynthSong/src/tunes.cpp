#include "tunes.h"

Tune::Tune() : _numNotes(0), _index(0) {
}

Tune::~Tune() {
}

float Tune::getNote() {
    // wrap index back to the beginning
    if(_index >= _numNotes) {
        _index = 0;
    }
    return _melody[_index++];
}


ArpeggioTune::ArpeggioTune() {
    _melody = {60, 64, 67, 71, 64, 67, 64, 69, 60, 55};
    _numNotes = _melody.size();
}

ArpeggioTune::~ArpeggioTune() {
}


FairyTune::FairyTune() {
    _melody = {81, 74, 70, 67, 79, 74, 70, 67, 78, 74, 70, 67, 79, 74, 70, 67,
                79, 72, 69, 65, 77, 72, 69, 65, 76, 72, 69, 65, 77, 72, 69, 65};
    _numNotes = _melody.size();
}

FairyTune::~FairyTune() {
}
