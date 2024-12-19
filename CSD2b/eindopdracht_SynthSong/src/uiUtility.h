#ifndef UIUTILITY_H
#define UIUTILITY_H

#include <iostream>

class UIUtility {
  public:

    static std::string retrieveSelection(std::string selectionOptions[], int numOptions);

    static int retrieveSelectionIndex(std::string selectionOptions[], int numOptions);

    static float retrieveValueInRange(float min, float max);

  protected:
    UIUtility() {}
    ~UIUtility() {}

    static bool validateSelection(std::string selection, std::string selectionOptions[],
                                    int numOptions);

    static std::string retrieveInput(std::string selectionOptions[], int numOptions);
};

#endif