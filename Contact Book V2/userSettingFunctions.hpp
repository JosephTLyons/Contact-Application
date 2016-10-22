#ifndef userSettingFunctions_hpp
#define userSettingFunctions_hpp

#include <vector>     //for using vectors

#include "personalInformation.hpp"

using namespace std;

/* USER SETTINGS FUNCTIONS */

void EncryptionOnOffSetting(bool &EncryptionMode);

void ScrollSpeedSettingsAndUserInput(const vector <personalInformation> &ContactVect,
                                     int &DisplaySpeed, int &SpeedSelectionChoice);

void ObtainSpeedSettingNumericalValues(int &DisplaySpeed, const int &SpeedSelectionChoice);

#endif /* userSettingFunctions_hpp */
