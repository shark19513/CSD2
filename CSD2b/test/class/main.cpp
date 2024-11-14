#include <iostream>

using namespace std;

/*
 * CLASS
 * 1. define class
 * 2. define constructor
 * 3. implement the constructor
 * 4. add fields/methods (and define)
*/

class Note {
public:
    // default constructor
    Note(); // same name as class name

    // methods (a method is a function in a class & a member of a class)
    // NOTE: for sake of example
    // play should usually not be part of Note class
    // void --> no return
    void play();
    // int --> returns integer
    int getVelocity();
    // fields (a field id a member of a class)
    int midiNoteValue;
    int velocity;
};

Note::Note() {
    cout << "Note - constructor\n";
    midiNoteValue = 0;
    velocity = 0;
}

void Note::play() {
    cout << "Playing note: " << midiNoteValue << " at velocity: " << velocity << std::endl;
}

int Note::getVelocity() {
    return velocity;
}

int main(){
    Note aNote;

    aNote.midiNoteValue = 60;
    aNote.velocity = 127;
    aNote.play();

    cout << "aNote.midiNoteValue contains: " << aNote.midiNoteValue << std::endl;
    cout << "aNote.velocity: " << aNote.velocity << std::endl;
}