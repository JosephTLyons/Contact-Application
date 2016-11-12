#ifndef miscellaneousFunctions_hpp
#define miscellaneousFunctions_hpp

#include <vector>     //for using vectors

#include "personalInformation.hpp"
#include "sortingFunctions.hpp"

/* MISCELLANEOUS FUNCTIONS */

void rebuildContactBook(vector<personalInformation> &contactVect, const char *path,
        int &speedSelectionChoice, bool &encryptionMode);

void readInUserSettings(int &speedSelectionChoice, bool &encryptionMode, int &amountOfContactsInFile, ifstream &fileIn);

void createFolderAndSettingsFile(char *fullPath);

bool checkIfFileExistsAndContainsInformation(const char *path);

void clearDataVectorsFromStructure(personalInformation &TemporaryStorage);

#endif /* miscellaneousFunctions_hpp */
