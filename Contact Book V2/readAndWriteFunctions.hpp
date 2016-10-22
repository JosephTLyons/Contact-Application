#ifndef readAndWriteFunctions_hpp
#define readAndWriteFunctions_hpp

#include <vector>     //for using vectors

using namespace std;

/* FUNCTIONS FROM READING AND WRITING FROM FILES AND FROM KEYBOARD */

void PrintVectorToFile(const vector <char> &ContactVect, ofstream &FileOut,
                       const bool &EncryptionMode);

void PrintVectorToScreen(const vector <char> &ContactVect);

void InsertStringInVectorFromFile(vector <char> &ContactVect, ifstream &FileIn,
                                  const bool &EncryptionMode);

void InsertStringDataVectorFromKeyboard(vector <char> &ContactVect);


#endif /* readAndWriteFunctions_hpp */
