#ifndef mainMenuFunctions_hpp
#define mainMenuFunctions_hpp

#include "personalinformation.hpp"

/* MAIN MENU FUNCTIONS */

void displayMainMenuOptions(const long int &numberOfContacts);

void displayAllContacts(const vector<personalInformation> &contactVect, const int &displaySpeed);

void printDividingLine();

void printSingleContact(const vector<personalInformation> &contactVect,
                        const int &vectorPos, const int &displaySpeed);

void displayVectors(const vector<personalInformation> &contactVect, const int &vectorPos);

void displayAge(const vector<personalInformation> &contactVect, const int &vectorPos);

void daysUntilBirthday(const vector<personalInformation> &contactVect, const int &vectorPos);

void addContact(vector<personalInformation> &contactVect, const bool &lastNameFirst);

void getContactInfoFromUser(personalInformation &temporary);

void editExistingContact(vector<personalInformation> &contactVect, const int &displaySpeed,
                         const bool &lastNameFirst);

void deleteContact(vector<personalInformation> &contactVect, const int &displaySpeed);

void deleteAllContacts(vector<personalInformation> &contactVect);

bool userWantsToDelete(const vector<char> &userChoice);

void displaySettingsMenu(vector<personalInformation> &contactVect, int &displaySpeed,
                         int &speedSelectionChoice, bool &encryptionMode, bool &lastNameFirst);

void searchForContacts(const vector<personalInformation> &contactVect, const int &displaySpeed);

bool searchContactsBasedOnCriteria(const personalInformation &contact,
                                   const vector<char> criteriaToSearchFor);

bool vectorsAreSame(const vector<char> &contact, const vector<char> &search);

#endif /* mainMenuFunctions_hpp */
