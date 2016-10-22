#include <iostream>   //for input/output stream

#include "dynamicBirthdayFunctions.hpp"

int BirthDayInput(personalInformation &TempPersonalInfoHolder)//not cleaned up
{
    /* USER ENTERS IN CONTACTS BIRTHDAY */
    
    cout << "\n  Enter Month (1 - 12): ";
    cin >> TempPersonalInfoHolder.MonthBorn;
    
    cout << "  Enter Day (1 - 31):   ";
    cin >> TempPersonalInfoHolder.DayBorn;
    
    cout << "  Enter Year (XXXX):    ";
    cin >> TempPersonalInfoHolder.YearBorn;
    
    /* STORE DATE OF BIRTH IN DATEOFBIRTH VECTOR */
    
    StoreDateOfBirthInVector(TempPersonalInfoHolder);
    
    return CalculateCurrentAge(TempPersonalInfoHolder, TempPersonalInfoHolder.MonthBorn, TempPersonalInfoHolder.DayBorn, TempPersonalInfoHolder.YearBorn);
} // BirthDayInput()

int CalculateCurrentAge(personalInformation &TempPersonalInfoHolder, const int &MonthBorn, const int &DayBorn, const int &YearBorn)//not cleaned up
{
    int DayOfTheYearBirthdayLandsOn = 0;
    int UsersCurrentAge = 0;
    
    char CurrentMonthOfThisYearString[3];//only 2 digits, EX 11 (November), +1 for null
    char CurrentDayOfThisYearString[4];//only 3 digits will ever be here, 365 days is 3 digits long, +1 for null
    char CurrentYearString[5];//only 4 digits will ever be here, EX. 2016 is 4 digits long, +1 for null
    
    int CurrentMonthOfThisYear = 0;
    int CurrentDayOfThisYear = 0;
    int CurrentYear = 0;
    
    time_t now = time(NULL);//Get current time/date
    
    /* GET CURRENT MONTH, CONVERT TO NUMBER, AND STORE IN THE ASSOCIATED INT */
    
    strftime(CurrentMonthOfThisYearString, 3, "%m", localtime(&now));//store month number in string
    
    for (int i = 0; CurrentMonthOfThisYearString[i]; i++)
    {
        CurrentMonthOfThisYear *= 10;
        CurrentMonthOfThisYear += (CurrentMonthOfThisYearString[i] - 48);
    }
    
    /* GET CURRENT DAY OF THIS YEAR, CONVERT TO NUMBER, AND STORE IN THE ASSOCIATED INT */
    
    strftime(CurrentDayOfThisYearString, 4, "%j", localtime(&now));//store day of year in string
    
    for (int i = 0; CurrentDayOfThisYearString[i]; i++)
    {
        CurrentDayOfThisYear *= 10;
        CurrentDayOfThisYear += (CurrentDayOfThisYearString[i] - 48);
    }
    
    /* GET CURRENT YEAR, CONVERT TO NUMBER, AND STORE IN THE ASSOCIATED INT */
    
    strftime(CurrentYearString, 5, "%Y", localtime(&now));//store current year in string
    
    for (int i = 0; CurrentYearString[i]; i++)
    {
        CurrentYear *= 10;
        CurrentYear += (CurrentYearString[i] - 48);
    }
    
    /* CALCULATE WHAT DAY OF THE YEAR THE USERS BIRTHDAY LANDS ON */
    
    DayOfTheYearBirthdayLandsOn = CalculateDayNumberFromMonthAndDay(MonthBorn, DayBorn, CurrentYear);
    
    UsersCurrentAge = CurrentYear - YearBorn;//Obtain age
    
    /* IF USERS BIRTHDAY HASN'T OCCURED THIS YEAR, THEN DECREMENT THEIR AGE BY 1 */
    
    if (CurrentDayOfThisYear < DayOfTheYearBirthdayLandsOn)
        --UsersCurrentAge;
    
    /* CALCULATE HOW CLOSE CONTACT'S BIRTHDAY IS */
    
    TempPersonalInfoHolder.BirthdayIsInXDays = DayOfTheYearBirthdayLandsOn - CurrentDayOfThisYear;
    
    return UsersCurrentAge;
} // CalculateCurrentAge()

int CalculateDayNumberFromMonthAndDay(const int &BirthMonth, const int &BirthDay, const int &CurrentYear)//not cleaned up
{
    int DayOfYearThatBirthdayIsOn = 0;
    int TemporaryDayHolder = 0;
    
    if (BirthMonth >= 1)//January - 31
    {
        DayOfYearThatBirthdayIsOn += TemporaryDayHolder;
        TemporaryDayHolder = 31;
    }
    
    if (BirthMonth >= 2)//February - 28/29
    {
        DayOfYearThatBirthdayIsOn += TemporaryDayHolder;
        TemporaryDayHolder = 28;
        
        /* CHECK TO SEE IF LEAP YEAR OR NOT */
        
        if (CurrentYear % 4 == 0)
        {
            if (CurrentYear % 100 == 0)
            {
                if (CurrentYear % 400 == 0)
                    TemporaryDayHolder = 29;
            }
            
            else
                TemporaryDayHolder = 29;
            
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
    
    if (BirthMonth >= 3)//March - 31
    {
        DayOfYearThatBirthdayIsOn += TemporaryDayHolder;
        TemporaryDayHolder = 31;
    }
    
    if (BirthMonth >= 4)//April - 30
    {
        DayOfYearThatBirthdayIsOn += TemporaryDayHolder;
        TemporaryDayHolder = 30;
    }
    
    if (BirthMonth >= 5)//May - 31
    {
        DayOfYearThatBirthdayIsOn += TemporaryDayHolder;
        TemporaryDayHolder = 31;
    }
    
    if (BirthMonth >= 6)//June - 30
    {
        DayOfYearThatBirthdayIsOn += TemporaryDayHolder;
        TemporaryDayHolder = 30;
    }
    
    if (BirthMonth >= 7)//July - 31
    {
        DayOfYearThatBirthdayIsOn += TemporaryDayHolder;
        TemporaryDayHolder = 31;
    }
    
    if (BirthMonth >= 8)//August - 31
    {
        DayOfYearThatBirthdayIsOn += TemporaryDayHolder;
        TemporaryDayHolder = 31;
    }
    
    if (BirthMonth >= 9)//September - 30
    {
        DayOfYearThatBirthdayIsOn += TemporaryDayHolder;
        TemporaryDayHolder = 30;
    }
    
    if (BirthMonth >= 10)//October - 31
    {
        DayOfYearThatBirthdayIsOn += TemporaryDayHolder;
        TemporaryDayHolder = 31;
    }
    
    if (BirthMonth >= 11)//November - 30
    {
        DayOfYearThatBirthdayIsOn += TemporaryDayHolder;
        TemporaryDayHolder = 30;
    }
    
    if (BirthMonth >= 12)//December - 31
    {
        DayOfYearThatBirthdayIsOn += TemporaryDayHolder;
        TemporaryDayHolder = 31;
    }
    
    DayOfYearThatBirthdayIsOn += BirthDay;
    
    return DayOfYearThatBirthdayIsOn;
} // CalculateDayNumberFromMonthAndDay()

void StoreDateOfBirthInVector(personalInformation &TempPersonalInfoHolder)//not cleaned up
{
    const char *MonthNames[12] = {"January",   "February", "March",    "April",
        "May",       "June",     "July",     "August",
        "September", "October",  "November", "December"};
    
    /* PLACING DATA MEMBERS INTO TEMPORARY VARIABLES BECAUSE THE VALUES OF THE VARIABLES WILL BE CHANGED */
    /* DONT WANT TO CHANGE THE DATA MEMBERS THOUGH */
    
    int TempMonth = TempPersonalInfoHolder.MonthBorn;
    int TempDay   = TempPersonalInfoHolder.DayBorn;
    int TempYear  = TempPersonalInfoHolder.YearBorn;
    
    char YearArray[5] = {0};//years limited to 4 digits - one day, we will have 5 digit years
    char DayArray[3]  = {0};//days limited to 2 digits - this is ok, will never be larger
    
    /* FIRST CHECK TO SEE IF BIRTHDAY WAS ENTERED - LATER CHANGE THIS TO JUST HITTING ENTER */
    
    if (TempPersonalInfoHolder.MonthBorn == 0)
    {
        if (TempPersonalInfoHolder.DayBorn == 0)
        {
            if (TempPersonalInfoHolder.YearBorn == 0)
            {
                TempPersonalInfoHolder.DateOfBirth.push_back('N');
                TempPersonalInfoHolder.DateOfBirth.push_back('/');
                TempPersonalInfoHolder.DateOfBirth.push_back('A');
                TempPersonalInfoHolder.DateOfBirth.push_back('\n');
                return;
            }
        }
    }
    
    /* INSERT MONTH NAME INTO DATEOFBIRTH VECTOR */
    
    for (int i = 0; MonthNames[TempMonth-1][i]; i++)
    {
        TempPersonalInfoHolder.DateOfBirth.push_back(MonthNames[TempMonth-1][i]);
    }
    
    TempPersonalInfoHolder.DateOfBirth.push_back(' ');
    
    /* STORE DAY IN CHAR ARRAY TO MAKE INSERTION IN DATEOFBIRTH VECTOR EASIER */
    
    for (int i = 1; i >= 0; i--)
    {
        DayArray[i] *= 10;
        DayArray[i] = (TempDay % 10) + 48;//convertion to char happens here
        TempDay /= 10;
    }
    
    /* INSERT DAY INTO DATEOFBIRTH VECTOR */
    
    for (int i = 0; DayArray[i]; i++)
        TempPersonalInfoHolder.DateOfBirth.push_back(DayArray[i]);
    
    TempPersonalInfoHolder.DateOfBirth.push_back(',');
    TempPersonalInfoHolder.DateOfBirth.push_back(' ');
    
    /* STORE YEAR IN CHAR ARRAY TO MAKE INSERTION IN DATEOFBIRTH VECTOR EASIER */
    
    for (int i = 3; i >= 0; i--)
    {
        YearArray[i] *= 10;
        YearArray[i] = (TempYear % 10) + 48;//convertion happens here
        TempYear /= 10;
    }
    
    /* INSERT YEAR INTO DATEOFBIRTH VECTOR */
    
    for (int i = 0; YearArray[i]; i++)
        TempPersonalInfoHolder.DateOfBirth.push_back(YearArray[i]);
    
    TempPersonalInfoHolder.DateOfBirth.push_back('\n');
} // StoreDateOfBirthInVector()
