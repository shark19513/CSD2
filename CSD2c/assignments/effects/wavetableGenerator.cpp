#include "wavetableGenerator.h"

void WavetableGenerator::generateWaveform(float* buffer,
                                          unsigned int bufferSize,
                                          waveFormType waveformType) {
  Oscillator* osc;
  float freq = 1.0;
  switch (waveformType) {
    case SINE: {
      osc = new Sine(static_cast<float>(bufferSize), freq);
        break;
    }
      case SAW: {
        osc = new Saw(static_cast<float>(bufferSize), freq);
        break;
    }
    case SQUARE: {
      // TODO: alter calculation to create not aliasing square
      osc = new Square(static_cast<float>(bufferSize), freq);
      break;
    }
    default:
      throw "WavetableGenerator::WavetableGenerator - incorrect waveformType.";
      break;
  }

  for (unsigned int i = 0; i < bufferSize; i++) {
    buffer[i] = osc->genNextSample();
  }
  delete osc;
  osc = nullptr;
}

void WavetableGenerator::generateSCurve(float *buffer,
                                        unsigned int bufferSize,
                                        float k) {
  float normalizeFactor = 1.0f / atan(k);
  for (unsigned int i = 0; i < bufferSize; i++) {
    // calculate s-curve with arctangent
    // calculate x in range [-1.0f, 1.0f]
    float x = Interpolation::mapInRange(static_cast<float>(i), 0,
                                static_cast<float>(bufferSize), -1.0f, 1.0f);
    buffer[i] = normalizeFactor * atan(k * x);
  }
}
