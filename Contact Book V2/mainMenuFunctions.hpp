#ifndef mainMenuFunctions_hpp
#define mainMenuFunctions_hpp

#include "personalinformation.hpp"

/* MAIN MENU FUNCTIONS */

void displayMainMenuOptions();

void DisplayContacts(const vector<personalInformation> &ContactVect, const int &DisplaySpeed);

void printDividingLine();

void printContact(const vector<personalInformation> &ContactVect, const int &VectorPos,
                  const int &displaySpeed);

void displayAge(const vector<personalInformation> &ContactVect, const int &VectorPos);

void daysUntilBirthday(const vector<personalInformation> &ContactVect, const int &VectorPos);

void AddContact(vector <personalInformation> &ContactVect);

void EditExistingContact(vector <personalInformation> &ContactVect, const int &DisplaySpeed);

void DeleteContact(vector <personalInformation> &ContactVect, const int &DisplaySpeed);

void DeleteAllContacts(vector <personalInformation> &ContactVect);

void DisplaySettingsMenu(const vector <personalInformation> &ContactVect,
                         int &DisplaySpeed, int &SpeedSelectionChoice, bool &EncryptionMode);

#endif /* mainMenuFunctions_hpp */
