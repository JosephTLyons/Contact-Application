#ifndef miscellaneousFunctions_hpp
#define miscellaneousFunctions_hpp

#include <vector>     //for using vectors

#include "personalInformation.hpp"
#include "sortingFunctions.hpp"

/* MISCELLANEOUS FUNCTIONS */

void RebuildContactBook(vector <personalInformation> &ContactVect, const char Path[], int &SpeedSelectionChoice, bool &EncryptionMode);
void CreateFolderAndTextFile(char FullPath[]);
bool CheckIfFileExistsAndContainsInformation(const char Path[]);
void ClearDataVectorsFromStructure(personalInformation &TemporaryStorage);

#endif /* miscellaneousFunctions_hpp */
