#ifndef sortingFunctions_hpp
#define sortingFunctions_hpp

#include <vector>     //for using vectors

#include "personalInformation.hpp"

/* SORTING FUNCTIONS */

void sortContactVector(vector<personalInformation> &contactVect, const bool &lastNameFirst);

void cycleThroughContacts(vector<personalInformation> &contactVect, bool &swapsMade);

bool namesInOrder(const vector<char> &LastNameVect1, const vector<char> &LastNameVect2,
        const vector<char> &FirstNameVect1, const vector<char> &FirstNameVect2);

#endif /* sortingFunctions_hpp */
