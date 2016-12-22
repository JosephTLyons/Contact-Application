#ifndef userSettingFunctions_hpp
#define userSettingFunctions_hpp

#include <vector>     //for using vectors

#include "personalInformation.hpp"

using namespace std;

/* USER SETTINGS FUNCTIONS */

void encryptionOnOffSetting(bool &encryptionMode);

void scrollSpeedSettingsAndUserInput(const vector<personalInformation> &contactVect,
        int &displaySpeed, int &speedSelectionChoice);

void obtainSpeedSettingNumericalValues(int &displaySpeed, const int &speedSelectionChoice);

bool lastNameFirstOrder(bool &lastNameFirst);

void lastNameFirstOrderMenu(bool &lastNameFirst);

#endif /* userSettingFunctions_hpp */
