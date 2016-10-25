#ifndef personalinformation_hpp
#define personalinformation_hpp

#include <vector>     //for using vectors

using namespace std;

struct personalInformation
{
    vector<char> firstNameVector;
    vector<char> lastNameVector;
    vector<char> addressVector;
    vector<char> phoneNumberVector;
    vector<char> dateOfBirthVector;
    
    int monthBorn;
    int dayBorn;
    int yearBorn;
    int currentAge;
    short int birthdayIsInXDays;
};

#endif /* personalinformation_hpp */
