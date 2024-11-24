#include "oscillator.h"

Oscillator::Oscillator() : Oscillator(440, 0, "sine")
{
  std::cout << "Inside Oscillator default constructor" << std::endl;
}

Oscillator::Oscillator(std::string waveform)
  :Oscillator(440, 0, waveform)
{
  std::cout << "Inside Oscillator secondary constructor" << std::endl;
}

Oscillator::Oscillator(float frequency, float amplitude, std::string waveform)
  : freq(frequency), amp(amplitude)
{
  std::cout << "Inside Oscillator third constructor" << std::endl;
  sound = waveform; //this string is from the SoundSource baseclass
}

Oscillator::~Oscillator()
{
  std::cout << "Inside Oscillator destructor" << std::endl;
}


// setters/getters
void Oscillator::setFrequency(float frequency)
{
  std::cout << "Inside Oscillator setFrequency" << std::endl;
  if (frequency > 0 && frequency < 22050) {
    this->freq = frequency;
  } else {
    std::cout << "Frequency out of range"
    << "\nPlease enter a frequency betweeen 0 and 22050" << std::endl;
  }
}

float Oscillator::getFrequency() {
  std::cout << "\nInside Oscillator getFrequency" << std::endl;
  return freq;
}
