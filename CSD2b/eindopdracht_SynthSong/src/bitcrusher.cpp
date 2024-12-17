#include "bitcrusher.h"

BitCrusher::BitCrusher() {
  std::cout<<"BitCrusher - constructor\n";
}

BitCrusher::~BitCrusher() {
  std::cout<<"BitCrusher - destructor\n";
}

//bitreduction
float BitCrusher::applyBitReduction(float sample) {
  float stepSize = 1.0f / (1 << _bitDepth);
  return std::round(sample / stepSize) * stepSize;
}