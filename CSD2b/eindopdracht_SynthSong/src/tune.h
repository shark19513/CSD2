#ifndef TUNE_H
#define TUNE_H

#include <iostream>

#define NUM_NOTES 10

class Tune {
  public:
    Tune();
    ~Tune();

    float getNote();

protected:
    //cmaj7 - arpeggio
    float _melody[NUM_NOTES] = {60, 64, 67, 71, 64, 67, 64, 69, 60, 55};
    // the index of the current note - readIndex
    int _index = 0;
};

#endif