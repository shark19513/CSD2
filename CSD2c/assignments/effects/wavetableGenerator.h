#ifndef WAVETABLEGENERATOR_H
#define WAVETABLEGENERATOR_H

#include <iostream>
#include "math.h"
#include <interpolation.h>
#include <sine.h>
#include <saw.h>
#include <square.h>


class WavetableGenerator {
public:
  enum waveFormType {
    SINE = 0,
    SAW,
    SQUARE,
    SIZE
  };

  // generate standard wavefrom in range [-1, 1]
  static void generateWaveform(float* buffer,
                               unsigned int bufferSize,
                               waveFormType waveFormType);

    // generates an s-curve in the range [-1, 1], based arctangent function
    // k: influences the curve,
    //    k < 1, mimics linear function
    //    k = 1, nearly linear
    //    k > 1, more 'curvy'
    //    k > 100, "square-like"
  static void generateSCurve(float* buffer,
                             unsigned int bufferSize,
                             float k);
private:
  WavetableGenerator(){}
};



#endif //WAVETABLEGENERATOR_H
