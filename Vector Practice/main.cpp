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

void MainMenu();
void SortVector(vector<PersonalInformation> &CV);
void AddContact(vector<PersonalInformation> &CV);
bool NamesInOrder(const char LastName1[], const char LastName2[], const char FirstName1[], const char FirstName2[]);

int main()
{
    MainMenu();
}

void MainMenu()
{
    vector<PersonalInformation> ContactVector;
    
    AddContact(ContactVector);
    
    cout << "Stop";
}

void AddContact(vector<PersonalInformation> &CV)
{
    PersonalInformation X;//temporary holding spot for input, used to store in vector
    char UserChoice;
    
    while (UserChoice != 'n' && UserChoice != 'N')
    {
        cout << "Enter First Name:   ";
        cin.getline(X.FirstName, FirstNameArraySize);
        X.FirstName[0] = toupper(X.FirstName[0]);//always capitalize first letter of first name
        
        cout << "Enter Last Name:    ";
        cin.getline(X.LastName, LastNameArraySize);
        X.LastName[0] = toupper(X.LastName[0]);//always capitalize first letter of last name
        
        cout << "Enter Address:      ";
        cin.getline(X.Address, AddressArraySize);
        
        cout << "Enter Phone Number: ";
        cin.getline(X.PhoneNumber, PhoneNumberArraySize);
        
        cout << "Enter Age:          ";
        cin >> X.Age;
        
        CV.push_back(X);
        
        cout << "\nAdd another contact? Y/N: ";
        cin >> UserChoice;
        cin.ignore();//removes newline left in input buffer after last cin >> statement
        cout << "\n";
        
        if (CV.size() > 1)
            SortVector(CV);
    }
}

void SortVector(vector<PersonalInformation> &CV)//not my code - bubble sort
{
    bool SwapsMade = true;
    
    while(SwapsMade)
    {
        SwapsMade = false;
        
        for (size_t i = 0; i < CV.size()-1; i++)
        {
            if (!NamesInOrder(CV[i].LastName, CV[i+1].LastName, CV[i].FirstName, CV[i+1].FirstName))
            {
                swap(CV[i], CV[i+1]);
                
                SwapsMade = true;
            }
        }
    }
}

bool NamesInOrder(const char LastName1[], const char LastName2[], const char FirstName1[], const char FirstName2[])
{
    //checks to see which last name comes first, if both last names are the same, it then uses the first name
    
    for (int i = 0; LastName1[i] || LastName2[i]; ++i)//go until you get to the end of the larger name
    {
        if(toupper(LastName1[i]) < toupper(LastName2[i]))
            return true;
        
        if(toupper(LastName1[i]) > toupper(LastName2[i]))
            return false;
    }
    
    for (int i = 0; FirstName1[i] || FirstName2[i]; ++i)//go until you get to the end of the larger name
    {
        if(toupper(FirstName1[i]) < toupper(FirstName2[i]))
            return true;
        
        if(toupper(FirstName1[i]) > toupper(FirstName2[i]))
            return false;
    }
    
    return true;//this will only be used if same last name and first name
}
