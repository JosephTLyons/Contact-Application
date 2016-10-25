#ifndef readAndWriteFunctions_hpp
#define readAndWriteFunctions_hpp

#include <vector>     //for using vectors

using namespace std;

/* FUNCTIONS FROM READING AND WRITING FROM FILES AND FROM KEYBOARD */

void printVectorToFile(const vector<char> &contactVect, ofstream &fileOut,
        const bool &encryptionMode);

void printVectorToScreen(const vector<char> &contactVect);

void insertStringInVectorFromFile(vector<char> &contactVect, ifstream &fileIn,
        const bool &encryptionMode);

void insertStringDataVectorFromKeyboard(vector<char> &contactVect);


#endif /* readAndWriteFunctions_hpp */
