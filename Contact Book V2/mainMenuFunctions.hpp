#ifndef mainMenuFunctions_hpp
#define mainMenuFunctions_hpp

#include "personalinformation.hpp"

/* MAIN MENU FUNCTIONS */

void displayMainMenuOptions();

void displayAllContacts(const vector<personalInformation> &contactVect, const int &displaySpeed);

void printDividingLine();

void printSingleContact(const vector<personalInformation> &contactVect, const int &vectorPos,
        const int &displaySpeed);

void displayVectors(const vector<personalInformation> &contactVect, const int &vectorPos);

void displayAge(const vector<personalInformation> &contactVect, const int &vectorPos);

void daysUntilBirthday(const vector<personalInformation> &contactVect, const int &vectorPos);

void addContact(vector<personalInformation> &contactVect);

void getContactInfoFromUser(personalInformation &temporary);

void editExistingContact(vector<personalInformation> &contactVect, const int &displaySpeed);

void deleteContact(vector<personalInformation> &contactVect, const int &displaySpeed);

void deleteAllContacts(vector<personalInformation> &contactVect);

bool userWantsToDelete(const vector<char> &userChoice);

void displaySettingsMenu(const vector<personalInformation> &contactVect,
        int &displaySpeed, int &speedSelectionChoice, bool &encryptionMode);

#endif /* mainMenuFunctions_hpp */
