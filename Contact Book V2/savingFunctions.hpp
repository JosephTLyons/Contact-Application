#ifndef savingFunctions_hpp
#define savingFunctions_hpp

#include <string.h> //for strcat function in pathway commands
#include <vector>   //for using vectors

#include "personalInformation.hpp"

/* FUNCTIONS FOR SAVING */

void SaveContactBookAndSettings(const vector <personalInformation> &ContactVect,
                                const char Path[], const int &SpeedSelectionChoice,
                                const bool &EncryptionMode);
string ObtainDateAndTime();

#endif /* savingFunctions_hpp */
