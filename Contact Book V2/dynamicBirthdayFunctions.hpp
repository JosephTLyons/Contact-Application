#ifndef dynamicBirthdayFunctions_hpp
#define dynamicBirthdayFunctions_hpp

#include "personalInformation.hpp"

/* FUNCTIONS FOR DYNAMIC AGE/BIRTHDAY */

int birthDayInput(personalInformation &tempPersonalInfoHolder);

int calculateCurrentAge(personalInformation &tempPersonalInfoHolder, const int &monthBorn,
        const int &dayBorn, const int &yearBorn);

int calculateDayNumberFromMonthAndDay(const int &birthMonth, const int &birthDay,
        const int &currentYear);

void storeDateOfBirthInVector(personalInformation &tempPersonalInfoHolder);

#endif /* dynamicBirthdayFunctions_hpp */
