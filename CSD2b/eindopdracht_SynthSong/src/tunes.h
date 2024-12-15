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

class ArpeggioTune : public Tune {    //cmaj7 - arpeggio
public:
    ArpeggioTune();
    ~ArpeggioTune();
};

class FairyTune : public Tune {
public:
  	FairyTune();
    ~FairyTune();
};

#endif