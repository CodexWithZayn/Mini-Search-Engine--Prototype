#ifndef INPUT_VALIDATION_H
#define INPUT_VALIDATION_H

#include <climits>
#include <string>


using namespace std;

namespace InputValidation {
int getValidInt(string prompt, int min = INT_MIN, int max = INT_MAX);
string getValidString(string prompt);
void pause();
} // namespace InputValidation

#endif
