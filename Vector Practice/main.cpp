#include <iostream>
#include <vector>

using namespace std;

struct PersonalInformation
{
    vector<char> FirstNameVector;
    vector<char> LastNameVector;
    vector<char> AddressVector;
    vector<char> PhoneNumberVector;
    
    int Age;
};

void MainMenu();
void DisplayContacts(const vector<PersonalInformation> &CV);
void AddContact(vector<PersonalInformation> &CV);
void InsertStringInStructDataVector(vector<char> &Vector);
void SortVector(vector<PersonalInformation> &CV);
bool NamesInOrder(vector<char> LastNameVect1, vector<char> LastNameVect2, vector<char> FirstNameVect1, vector<char> FirstNameVect2);

int main()
{
    //load list into vector from file
    MainMenu();
    //save list to file from vector
}

void MainMenu()
{
    vector<PersonalInformation> ContactVector;
    int Choice;
    
    do
    {
        cout << "(1) Display List";
        
        cout << "\n(2) Add Contact";
        
        cout << "\n(3) Delete Contact";
        
        cout << "\n(4) Exit";
        
        cout << "\n\nChoice: ";
        
        cin >> Choice;
        
        cout << "\n";
        
        switch (Choice)
        {
            case 1:
                DisplayContacts(ContactVector);
                
                break;
                
            case 2:
            {
                cin.ignore();//remove newline before jumping into AddContact(), or it won't work properly
                AddContact(ContactVector);
            }
                
                break;
                
            case 3:
                cout << "Something";
                
                break;
                
            default:
                break;
        }
        
        
    }
    while (Choice != 4);
}

void DisplayContacts(const vector<PersonalInformation> &CV)
{
    for (int ForLoopOneCounter = 0; ForLoopOneCounter < CV.size(); ForLoopOneCounter++)
    {
        
        cout << "First Name:   ";
        for (int j = 0; j < CV[ForLoopOneCounter].FirstNameVector.size(); j++)
        {
            cout << CV[ForLoopOneCounter].FirstNameVector[j];
        }
        
        cout << "Last Name:    ";
        for (int j = 0; j < CV[ForLoopOneCounter].LastNameVector.size(); j++)
        {
            cout << CV[ForLoopOneCounter].LastNameVector[j];
        }
        
        cout << "Address:      ";
        for (int j = 0; j < CV[ForLoopOneCounter].AddressVector.size(); j++)
        {
            cout << CV[ForLoopOneCounter].AddressVector[j];
        }
        
        cout << "Phone Number: ";
        for (int j = 0; j < CV[ForLoopOneCounter].PhoneNumberVector.size(); j++)
        {
            cout << CV[ForLoopOneCounter].PhoneNumberVector[j];
        }
        
        cout << "Age:          ";
        cout << CV[ForLoopOneCounter].Age;
        
        cout << "\n\n";
    }
    
    //use code to slow down output
}

void AddContact(vector<PersonalInformation> &CV)
{
    PersonalInformation Temp;//temporary holding spot for input, used to store in vector
    char UserChoice;
    
    while (UserChoice != 'n' && UserChoice != 'N')
    {
        cout << "Enter First Name:   ";
        InsertStringInStructDataVector(Temp.FirstNameVector);
        
        cout << "Enter Last Name:    ";
        InsertStringInStructDataVector(Temp.LastNameVector);
        
        cout << "Enter Address:      ";
        InsertStringInStructDataVector(Temp.AddressVector);
        
        cout << "Enter Phone Number: ";
        InsertStringInStructDataVector(Temp.PhoneNumberVector);
        
        cout << "Enter Age:          ";
        cin >> Temp.Age;
        
        CV.push_back(Temp);//store Temp in ContactVector Vector
        
        Temp.FirstNameVector.clear();//clear out all vectors of temporary storage to get ready for next
        Temp.LastNameVector.clear();
        Temp.AddressVector.clear();
        Temp.PhoneNumberVector.clear();
        
        if (CV.size() > 1)//don't go into sort function if only one name is in vector
            SortVector(CV);
        
        cout << "\nAdd another contact? Y/N: ";
        cin >> UserChoice;
        cin.ignore();//removes newline left in input buffer after last cin >> statement
        cout << "\n";
    }
}

void InsertStringInStructDataVector(vector<char> &Vector)
{
    char Insert = 0;//used for inserting characters into individual struct vectors
                       //initialized at 0 to allow while loop to execute
    
    while (Insert != '\n')
    {
        cin.get(Insert);//using cin.get, and not cin >>, so it stores the newline in Insert - allows to break out of loop
        
        Vector.push_back(Insert);
    }
    
    if (!isnumber(Vector[0]))
        (Vector[0] = toupper(Vector[0]));//if not a number, always capitalize (for first name and last names)
}

void SortVector(vector<PersonalInformation> &CV)//not my code - bubble sort
{
    bool SwapsMade = true;
    
    while(SwapsMade)
    {
        SwapsMade = false;
        
        for (size_t i = 0; i < CV.size()-1; i++)//research what size_t is
        {
            if (!NamesInOrder(CV[i].LastNameVector, CV[i+1].LastNameVector, CV[i].FirstNameVector, CV[i+1].FirstNameVector))
            {
                swap(CV[i], CV[i+1]);
                
                SwapsMade = true;
            }
        }
    }
}

bool NamesInOrder(vector<char> LastNameVect1, vector<char> LastNameVect2, vector<char> FirstNameVect1, vector<char> FirstNameVect2)
{
    //checks to see which last name comes first, if both last names are the same, it then uses the first name
    
    for (int i = 0; LastNameVect1[i] || LastNameVect2[i]; ++i)//go until you get to the end of the larger name
    {
        if(toupper(LastNameVect1[i]) < toupper(LastNameVect2[i]))
            return true;
        
        if(toupper(LastNameVect1[i]) > toupper(LastNameVect2[i]))
            return false;
    }
    
    for (int i = 0; FirstNameVect1[i] || FirstNameVect2[i]; ++i)//go until you get to the end of the larger name
    {
        if(toupper(FirstNameVect1[i]) < toupper(FirstNameVect2[i]))
            return true;
        
        if(toupper(FirstNameVect1[i]) > toupper(FirstNameVect2[i]))
            return false;
    }
    
    return true;//if both names are identical, return true
                //no swap will be made back in SortVector() function
}
