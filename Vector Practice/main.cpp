#include <iostream>
#include <vector>

using namespace std;

struct PersonalInformation
{
    char FirstName[20];
    char LastName[20];
    char Address[40];
    char PhoneNumber[15];
    
    int Age;
};

void SortVector(vector<int> VN);

int main()
{
    vector<int> VectorNumber;
    int UserNumber;
    
    for(int i = 0; i < 10; i++)
    {
        cin >> UserNumber;
        VectorNumber.push_back(UserNumber);
    }
    
    SortVector(VectorNumber);
}

void SortVector(vector<int> VN)
{
    
}