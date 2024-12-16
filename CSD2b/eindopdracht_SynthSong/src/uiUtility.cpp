#include "uiUtility.h"

std::string UIUtility::retrieveSelection(std::string selectionOptions[], int numOptions) {
  bool noCorrectSelection = true;
  std::string userSelection = "";

  while (noCorrectSelection) {
    userSelection = retrieveInput(selectionOptions, numOptions);
    noCorrectSelection = !validateSelection(userSelection, selectionOptions, numOptions);

    if (noCorrectSelection) {
      std::cout << "Invalid input, please try again.";
    }
  }
  return userSelection;
}

int UIUtility::retrieveSelectionIndex(std::string selectionOptions[], int numOptions) {
  std::string userSelection = retrieveSelection(selectionOptions, numOptions);

  for (int i = 0; i < numOptions; i++) {
    if (userSelection == selectionOptions[i]) {
      return i;
    }
  }
  std::cout << "ERROR • UIUtilities::retrieveUserSelection - "
            << "THIS SHOULD NEVER HAPPEN" << std::endl;
  throw "ERROR • UIUtilities::retrieveUserSelection";
  return -1;
}

float UIUtility::retrieveValueInRange(float min, float max) {
  std::string input;
  float value = 0;
  bool notInRange = true;

  while (notInRange) {
    std::cout << "Please enter a value between " << min << " and " << max << ": " << std::endl;
    std::cin >> input;
    try {
      value = std::stof(input);
      if (value >= min && value <= max) {
        notInRange = false;
      } else {
        std::cout << "Invalid input, please try again" << std::endl;
      }
    } catch (const std::exception& e) {
      // no float as input?
      std::cout << "Invalid input, please enter a number" << std::endl;
    }
  }
  return value;
}

bool UIUtility::validateSelection(std::string selection, std::string selectionOptions[],
                                int numOptions) {
  for (int i = 0; i < numOptions; i++) {
    if (selection == selectionOptions[i]) {
      return true;
    }
  }
  return false;
}

std::string UIUtility::retrieveInput(std::string selectionOptions[], int numOptions) {
  std::cout << "Please enter selection from following options: ";
  for (int i = 0; i < numOptions -1; i++) {
    std::cout << selectionOptions[i] << ", ";
  }
  std::cout << selectionOptions[numOptions - 1] << "." << std::endl;
  std::string selection = "";
  std::cin >> selection;
  return selection;
}