#ifndef dynamicBirthdayFunctions_hpp
#define dynamicBirthdayFunctions_hpp

#include "personalInformation.hpp"

/* FUNCTIONS FOR DYNAMIC AGE/BIRTHDAY */

int BirthDayInput(personalInformation &TempPersonalInfoHolder);
int CalculateCurrentAge(personalInformation &TempPersonalInfoHolder, const int &MonthBorn, const int &DayBorn, const int &YearBorn);
int CalculateDayNumberFromMonthAndDay(const int &BirthMonth, const int &BirthDay, const int &CurrentYear);
void StoreDateOfBirthInVector(personalInformation &TempPersonalInfoHolder);

#endif /* dynamicBirthdayFunctions_hpp */
