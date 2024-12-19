#include "bitcrusher.h"

BitCrusher::BitCrusher() {
}

BitCrusher::~BitCrusher() {
}


//bitreduction
float BitCrusher::applyBitReduction(float sample) {
  float stepSize = 1.0f / (1 << _bitDepth);
  return std::round(sample / stepSize) * stepSize;
}

void BitCrusher::setBitDepth(float bitDepth) {
  // convert to int in case user inputs a float
  this->_bitDepth = (int)bitDepth;
  std::cout << "- Bit depth set to " << _bitDepth << " -" << std::endl;
}

void BitCrusher::setBypassState(bool bypass) {
  this->_bypassState = bypass;
  if (!bypass) {
    std::cout <<"- Bitcrusher enabled -" << std::endl;
  } else {
    std::cout <<"- Bitcrusher disabled -" << std::endl;
  }
}

bool BitCrusher::getBypassState() {
  return _bypassState;
}