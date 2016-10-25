#include <iostream>   //for input/output stream

#include "dynamicBirthdayFunctions.hpp"

int birthDayInput(personalInformation &tempPersonalInfoHolder)//not cleaned up
{
    /* USER ENTERS IN CONTACTS BIRTHDAY */
    
    cout << "\n  Enter Month (1 - 12): ";
    cin >> tempPersonalInfoHolder.monthBorn;
    
    cout << "  Enter Day (1 - 31):   ";
    cin >> tempPersonalInfoHolder.dayBorn;
    
    cout << "  Enter Year (XXXX):    ";
    cin >> tempPersonalInfoHolder.yearBorn;
    
    /* STORE DATE OF BIRTH IN DATEOFBIRTH VECTOR */

    storeDateOfBirthInVector(tempPersonalInfoHolder);
    
    return calculateCurrentAge(tempPersonalInfoHolder, tempPersonalInfoHolder.monthBorn, tempPersonalInfoHolder.dayBorn, tempPersonalInfoHolder.yearBorn);
} // birthDayInput()

int calculateCurrentAge(personalInformation &tempPersonalInfoHolder, const int &monthBorn, const int &dayBorn, const int &yearBorn)//not cleaned up
{
    int dayOfTheYearBirthdayLandsOn = 0;
    int usersCurrentAge = 0;
    
    char currentMonthOfThisYearString[3];//only 2 digits, EX 11 (November), +1 for null
    char currentDayOfThisYearString[4];//only 3 digits will ever be here, 365 days is 3 digits long, +1 for null
    char currentYearString[5];//only 4 digits will ever be here, EX. 2016 is 4 digits long, +1 for null
    
    int currentMonthOfThisYear = 0;
    int currentDayOfThisYear = 0;
    int currentYear = 0;
    
    time_t now = time(NULL);//Get current time/date
    
    /* GET CURRENT MONTH, CONVERT TO NUMBER, AND STORE IN THE ASSOCIATED INT */
    
    strftime(currentMonthOfThisYearString, 3, "%m", localtime(&now));//store month number in string
    
    for (int i = 0; currentMonthOfThisYearString[i]; i++)
    {
        currentMonthOfThisYear *= 10;
        currentMonthOfThisYear += (currentMonthOfThisYearString[i] - 48);
    }
    
    /* GET CURRENT DAY OF THIS YEAR, CONVERT TO NUMBER, AND STORE IN THE ASSOCIATED INT */
    
    strftime(currentDayOfThisYearString, 4, "%j", localtime(&now));//store day of year in string
    
    for (int i = 0; currentDayOfThisYearString[i]; i++)
    {
        currentDayOfThisYear *= 10;
        currentDayOfThisYear += (currentDayOfThisYearString[i] - 48);
    }
    
    /* GET CURRENT YEAR, CONVERT TO NUMBER, AND STORE IN THE ASSOCIATED INT */
    
    strftime(currentYearString, 5, "%Y", localtime(&now));//store current year in string
    
    for (int i = 0; currentYearString[i]; i++)
    {
        currentYear *= 10;
        currentYear += (currentYearString[i] - 48);
    }
    
    /* CALCULATE WHAT DAY OF THE YEAR THE USERS BIRTHDAY LANDS ON */
    
    dayOfTheYearBirthdayLandsOn = calculateDayNumberFromMonthAndDay(monthBorn, dayBorn, currentYear);
    
    usersCurrentAge = currentYear - yearBorn;//Obtain age
    
    /* IF USERS BIRTHDAY HASN'T OCCURED THIS YEAR, THEN DECREMENT THEIR AGE BY 1 */
    
    if (currentDayOfThisYear < dayOfTheYearBirthdayLandsOn)
        --usersCurrentAge;
    
    /* CALCULATE HOW CLOSE CONTACT'S BIRTHDAY IS */
    
    tempPersonalInfoHolder.birthdayIsInXDays = dayOfTheYearBirthdayLandsOn - currentDayOfThisYear;
    
    return usersCurrentAge;
} // calculateCurrentAge()

int calculateDayNumberFromMonthAndDay(const int &birthMonth, const int &birthDay, const int &currentYear)//not cleaned up
{
    int dayOfYearThatBirthdayIsOn = 0;
    int temporaryDayHolder = 0;
    
    if (birthMonth >= 1)//January - 31
    {
        dayOfYearThatBirthdayIsOn += temporaryDayHolder;
        temporaryDayHolder = 31;
    }
    
    if (birthMonth >= 2)//February - 28/29
    {
        dayOfYearThatBirthdayIsOn += temporaryDayHolder;
        temporaryDayHolder = 28;
        
        /* CHECK TO SEE IF LEAP YEAR OR NOT */
        
        if (currentYear % 4 == 0)
        {
            if (currentYear % 100 == 0)
            {
                if (currentYear % 400 == 0)
                    temporaryDayHolder = 29;
            }
            
            else
                temporaryDayHolder = 29;
            
        }
        
        /* - ALGORITH AB0VE DERIVED FROM
         
         https://support.microsoft.com/en-us/kb/214019
         
         1. If the year is evenly divisible by 4, go to step 2. Otherwise, go to step 5.
         2. If the year is evenly divisible by 100, go to step 3. Otherwise, go to step 4.
         3. If the year is evenly divisible by 400, go to step 4. Otherwise, go to step 5.
         4. The year is a leap year (it has 366 days).
         5. The year is not a leap year (it has 365 days).
         
         */
        
    }
    
    if (birthMonth >= 3)//March - 31
    {
        dayOfYearThatBirthdayIsOn += temporaryDayHolder;
        temporaryDayHolder = 31;
    }
    
    if (birthMonth >= 4)//April - 30
    {
        dayOfYearThatBirthdayIsOn += temporaryDayHolder;
        temporaryDayHolder = 30;
    }
    
    if (birthMonth >= 5)//May - 31
    {
        dayOfYearThatBirthdayIsOn += temporaryDayHolder;
        temporaryDayHolder = 31;
    }
    
    if (birthMonth >= 6)//June - 30
    {
        dayOfYearThatBirthdayIsOn += temporaryDayHolder;
        temporaryDayHolder = 30;
    }
    
    if (birthMonth >= 7)//July - 31
    {
        dayOfYearThatBirthdayIsOn += temporaryDayHolder;
        temporaryDayHolder = 31;
    }
    
    if (birthMonth >= 8)//August - 31
    {
        dayOfYearThatBirthdayIsOn += temporaryDayHolder;
        temporaryDayHolder = 31;
    }
    
    if (birthMonth >= 9)//September - 30
    {
        dayOfYearThatBirthdayIsOn += temporaryDayHolder;
        temporaryDayHolder = 30;
    }
    
    if (birthMonth >= 10)//October - 31
    {
        dayOfYearThatBirthdayIsOn += temporaryDayHolder;
        temporaryDayHolder = 31;
    }
    
    if (birthMonth >= 11)//November - 30
    {
        dayOfYearThatBirthdayIsOn += temporaryDayHolder;
        temporaryDayHolder = 30;
    }
    
    if (birthMonth >= 12)//December - 31
    {
        dayOfYearThatBirthdayIsOn += temporaryDayHolder;
        temporaryDayHolder = 31;
    }
    
    dayOfYearThatBirthdayIsOn += birthDay;
    
    return dayOfYearThatBirthdayIsOn;
} // calculateDayNumberFromMonthAndDay()

void storeDateOfBirthInVector(personalInformation &tempPersonalInfoHolder)//not cleaned up
{
    const char *monthNames[12] = {"January",   "February", "March",    "April",
        "May",       "June",     "July",     "August",
        "September", "October",  "November", "December"};
    
    /* PLACING DATA MEMBERS INTO TEMPORARY VARIABLES BECAUSE THE VALUES OF THE VARIABLES WILL BE CHANGED */
    /* DONT WANT TO CHANGE THE DATA MEMBERS THOUGH */
    
    int tempMonth = tempPersonalInfoHolder.monthBorn;
    int tempDay   = tempPersonalInfoHolder.dayBorn;
    int tempYear  = tempPersonalInfoHolder.yearBorn;
    
    char yearArray[5] = {0};//years limited to 4 digits - one day, we will have 5 digit years
    char dayArray[3]  = {0};//days limited to 2 digits - this is ok, will never be larger
    
    /* FIRST CHECK TO SEE IF BIRTHDAY WAS ENTERED - LATER CHANGE THIS TO JUST HITTING ENTER */
    
    if (tempPersonalInfoHolder.monthBorn == 0)
    {
        if (tempPersonalInfoHolder.dayBorn == 0)
        {
            if (tempPersonalInfoHolder.yearBorn == 0)
            {
                tempPersonalInfoHolder.dateOfBirthVector.push_back('N');
                tempPersonalInfoHolder.dateOfBirthVector.push_back('/');
                tempPersonalInfoHolder.dateOfBirthVector.push_back('A');
                tempPersonalInfoHolder.dateOfBirthVector.push_back('\n');
                return;
            }
        }
    }
    
    /* INSERT MONTH NAME INTO DATEOFBIRTH VECTOR */
    
    for (int i = 0; monthNames[tempMonth-1][i]; i++)
    {
        tempPersonalInfoHolder.dateOfBirthVector.push_back(monthNames[tempMonth-1][i]);
    }
    
    tempPersonalInfoHolder.dateOfBirthVector.push_back(' ');
    
    /* STORE DAY IN CHAR ARRAY TO MAKE INSERTION IN DATEOFBIRTH VECTOR EASIER */
    
    for (int i = 1; i >= 0; i--)
    {
        dayArray[i] *= 10;
        dayArray[i] = (tempDay % 10) + 48;//convertion to char happens here
        tempDay /= 10;
    }
    
    /* INSERT DAY INTO DATEOFBIRTH VECTOR */
    
    for (int i = 0; dayArray[i]; i++)
        tempPersonalInfoHolder.dateOfBirthVector.push_back(dayArray[i]);
    
    tempPersonalInfoHolder.dateOfBirthVector.push_back(',');
    tempPersonalInfoHolder.dateOfBirthVector.push_back(' ');
    
    /* STORE YEAR IN CHAR ARRAY TO MAKE INSERTION IN DATEOFBIRTH VECTOR EASIER */
    
    for (int i = 3; i >= 0; i--)
    {
        yearArray[i] *= 10;
        yearArray[i] = (tempYear % 10) + 48;//convertion happens here
        tempYear /= 10;
    }
    
    /* INSERT YEAR INTO DATEOFBIRTH VECTOR */
    
    for (int i = 0; yearArray[i]; i++)
        tempPersonalInfoHolder.dateOfBirthVector.push_back(yearArray[i]);
    
    tempPersonalInfoHolder.dateOfBirthVector.push_back('\n');
} // storeDateOfBirthInVector()
