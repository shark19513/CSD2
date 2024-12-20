#ifndef TUNES_H
#define TUNES_H

#include <iostream>

class Tune {
public:
	Tune();
    ~Tune();

	int getNote();

protected:
    int _numNotes;
    uint8_t _index;
    std::vector<int> _melody;
};

struct ArpeggioTune : Tune {
    ArpeggioTune();
    ~ArpeggioTune();
};

struct FairyTune : Tune {
  	FairyTune();
    ~FairyTune();
};

#endif