#include <iostream>
#include <vector>

using namespace std;

const short int FirstNameArraySize   = 20;
const short int LastNameArraySize    = 20;
const short int AddressArraySize     = 50;
const short int PhoneNumberArraySize = 20;

struct PersonalInformation
{
    char FirstName[FirstNameArraySize];
    char LastName[LastNameArraySize];
    char Address[AddressArraySize];
    char PhoneNumber[PhoneNumberArraySize];
    
    int Age;
};

void SortVector(vector<int> &VN);

int main()
{
    PersonalInformation X;//temporary holding spot for input;
    vector<PersonalInformation> ContactVector;
    
    
    cout << "Enter First Name: ";
    cin.getline(X.FirstName, FirstNameArraySize);
    
    cout << "Enter Last Name: ";
    cin.getline(X.LastName, LastNameArraySize);
    
    cout << "Enter Address: ";
    cin.getline(X.Address, AddressArraySize);
    
    cout << "Enter Phone Number: ";
    cin.getline(X.PhoneNumber, PhoneNumberArraySize);
    
    cout << "Enter Age: ";
    cin >> X.Age;
    
    ContactVector.push_back(X);
    
    //SortVector(VectorNumber);
    
    cout << "Stop";
}

void SortVector(vector<int> &VN)//not my code
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