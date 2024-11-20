#include <iostream>

class Woofer {
  public:
  // default constructor
  Woofer();
  // overloaded constructor
  Woofer(float diam);

  //fields
  float diameter;
  float conePosition;
};

Woofer::Woofer() {
  std::cout << "Woofer - default constructor" << std::endl;

  diameter = 8.0f;
  conePosition = 0.0f;
}

Woofer::Woofer(float diam) {
  std::cout << "Woofer - overloaded constructor" << std::endl;

  diameter = diam;
  conePosition = 0.0f;
}

class Tweeter{
public:
  // default constructor
  Tweeter();
  // overloaded constructor
  Tweeter(float diam);

  // fields
  float diameter;
  float conePosition;
};

Tweeter::Tweeter() {
  std::cout << "Tweeter - default constructor\n";
  // NOTE: duplicate code alarm!!
  // constructor delegation is a better strategy!

  // in cm
  diameter = 2.5f;
  // number with an f --> indicate it is a float
  conePosition = 0.0f;
}

Tweeter::Tweeter(float diam) {
  std::cout << "Tweeter - overloaded constructor\n";
  // in cm
  diameter = diam;
  // number with an f --> indicate it is a float
  conePosition = 0.0f;
}

class Speaker{
public:
  Speaker();

  Tweeter aTweeter{3};
  Woofer aWoofer{9};
};

Speaker::Speaker() {
  std::cout << "Speaker - constructor\n";
  aTweeter.diameter = 2.4;
  std::cout << "The diameter of the tweeter is: "
    << aTweeter.diameter << "\n";

  aWoofer.diameter = 7;
  std::cout << "The diameter of the woofer is: "
    << aWoofer.diameter << "\n";
}

int main() {
  Speaker aSpeaker;
};