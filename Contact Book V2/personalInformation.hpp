#ifndef personalinformation_hpp
#define personalinformation_hpp

#include <vector>     //for using vectors

using namespace std;

struct personalInformation
{
    vector<char> FirstNameVector;
    vector<char> LastNameVector;
    vector<char> AddressVector;
    vector<char> PhoneNumberVector;
    vector<char> DateOfBirth;
    
    int MonthBorn;
    int DayBorn;
    int YearBorn;
    int CurrentAge;
    short int BirthdayIsInXDays;
};

#endif /* personalinformation_hpp */
