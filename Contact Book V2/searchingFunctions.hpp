#ifndef searchingFunctions_hpp
#define searchingFunctions_hpp

#include <vector>     //for using vectors

#include "personalInformation.hpp"

void searchForContacts(const vector<personalInformation> &contactVect, const int &displaySpeed);

bool searchContactsBasedOnCriteria(const personalInformation &contact,
                                   const vector<char> criteriaToSearchFor);

bool vectorsAreSame(const vector<char> &contact, const vector<char> &search);

#endif /* searchingFunctions_hpp */
