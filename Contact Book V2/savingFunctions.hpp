#ifndef savingFunctions_hpp
#define savingFunctions_hpp

#include <string.h> //for strcat function in pathway commands
#include <vector>   //for using vectors

#include "personalInformation.hpp"

/* FUNCTIONS FOR SAVING */

void saveContactBookAndSettings(const vector<personalInformation> &contactVect,
        const char *path, const int &speedSelectionChoice,
        const bool &encryptionMode);

string obtainDateAndTime();

#endif /* savingFunctions_hpp */
