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

void SortVector(vector<int> &VN);

int main()
{
    vector<PersonalInformation> ContactVector;
    
    vector<int> VectorNumber;
    int UserNumber;
    
    for(int i = 0; UserNumber != 1; i++)
    {
        cin >> UserNumber;
        VectorNumber.push_back(UserNumber);
    }
    
    SortVector(VectorNumber);
    
    cout << "stop";
}

void SortVector(vector<int> &VN)
{
    //cout << VN.size();//returns number of elements in vector
    
    bool swapp = true;
    
    while(swapp)
    {
        swapp = false;
        
        for (size_t i = 0; i < VN.size()-1; i++)
        {
            if (VN[i] > VN[i+1])
            {
                VN[i] += VN[i+1];
                
                VN[i+1] = VN[i] - VN[i+1];
                
                VN[i] -= VN[i+1];
                
                swapp = true;
            }
        }
    }
}