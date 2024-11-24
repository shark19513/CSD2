#ifndef KEYBOARD_H
#define KEYBOARD_H

class Keyboard {
  public:
    Keyboard();
    Keyboard(int numOfKeys);
    ~Keyboard();

    int keys;
};

#endif