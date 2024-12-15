#ifndef TUNES_H
#define TUNES_H

#include <iostream>

class Tune {
public:
	Tune();
    ~Tune();

	float getNote();

protected:
    int _numNotes;
    // the index of the current note - readIndex
    int _index;
    std::vector<float> _melody;
};

struct ArpeggioTune : Tune {    //cmaj7 - arpeggio
    ArpeggioTune();
    ~ArpeggioTune();
};

struct FairyTune : Tune {
  	FairyTune();
    ~FairyTune();
};

#endif