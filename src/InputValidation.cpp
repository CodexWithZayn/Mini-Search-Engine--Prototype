#include "InputValidation.h"
#include "Colors.h"
#include <iostream>
#include <limits.h>
#include <limits>

using namespace std;

namespace InputValidation {

int getValidInt(string prompt, int min, int max) {
  int value;
  while (true) {
    cout << CYAN << prompt << RESET;
    if (cin >> value) {
      cin.ignore(numeric_limits<streamsize>::max(), '\n');

      if (value >= min && value <= max) {
        return value;
      } else {
        cout << RED << " [INVALID] Please enter a number between " << min
             << " and " << max << ".\n"
             << RESET;
      }
    } else {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << RED << " [INVALID] Please enter a valid number.\n" << RESET;
    }
  }
}

string getValidString(string prompt) {
  string value;
  while (true) {
    cout << CYAN << prompt << RESET;
    getline(cin, value);

    // Basic validation: ensure not empty
    bool isEmpty = true;
    for (char c : value) {
      if (!isspace(c)) {
        isEmpty = false;
        break;
      }
    }

    if (!isEmpty) {
      return value;
    } else {
      cout << RED << " [INVALID] Input cannot be empty! Please try again.\n"
           << RESET;
    }
  }
}

void pause() {
  cout << "\n" << CYAN << "Press Enter to continue..." << RESET;
  cin.get();
}
} // namespace InputValidation
