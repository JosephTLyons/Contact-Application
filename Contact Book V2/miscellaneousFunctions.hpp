#ifndef miscellaneousFunctions_hpp
#define miscellaneousFunctions_hpp

#include <vector>     //for using vectors

#include "personalInformation.hpp"
#include "sortingFunctions.hpp"

/* MISCELLANEOUS FUNCTIONS */

void rebuildContactBook(vector<personalInformation> &contactVect, const char *path,
        int &speedSelectionChoice, bool &encryptionMode);

void readInUserSettings(int &speedSelectionChoice, bool &encryptionMode,
                        int &amountOfContactsInFile, ifstream &fileIn);

void createFolderAndSettingsFile(char *fullPath);

bool checkIfFileExistsAndContainsInformation(const char *path);

void emptyVectorsInStruct(personalInformation &TemporaryStorage);

void deleteVectorMemoryAndClear(vector<char> &vect);

void searchForContacts(const vector<personalInformation> &contactVect, const int &displaySpeed);

bool searchContactsBasedOnCriteria(const personalInformation &contact,
                                   const vector<char> criteriaToSearchFor,
                                   const int &i, const int &j);

bool compareVectors(const vector<char> &vector1, const vector<char> &vector2);

#endif /* miscellaneousFunctions_hpp */
