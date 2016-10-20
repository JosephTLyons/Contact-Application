#ifndef sortingFunctions_hpp
#define sortingFunctions_hpp

#include <vector>     //for using vectors

#include "personalInformation.hpp"

/* SORTING FUNCTIONS */

void SortContactVector(vector <personalInformation> &ContactVect);
bool NamesInOrder(const vector <char> &LastNameVect1, const vector <char> &LastNameVect2,
                  const vector <char> &FirstNameVect1, const vector <char> &FirstNameVect2);

#endif /* sortingFunctions_hpp */
