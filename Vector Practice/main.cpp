#include <iostream>

#include <ctype.h>//for toupper function
#include <unistd.h>//for usleep function
#include <vector>

using namespace std;

struct PersonalInformation
{
    vector<char> FirstNameVector;
    vector<char> LastNameVector;
    vector<char> AddressVector;
    vector<char> PhoneNumberVector;
    
    short int Age;
};

void MainMenu();
void DisplayContacts(const vector<PersonalInformation> &CV);
void PrintStringInStructDataVector(const vector<char> &Vector);
void AddContact(vector<PersonalInformation> &CV);
void InsertStringInStructDataVector(vector<char> &Vector);
void DeleteContact(vector<PersonalInformation> &CV);
void SortVector(vector<PersonalInformation> &CV);
bool NamesInOrder(vector<char> LastNameVect1, vector<char> LastNameVect2, vector<char> FirstNameVect1, vector<char>
                  FirstNameVect2);
bool NamesSame(vector<char> LastNameVect1, vector<char> LastNameVect2, vector<char> FirstNameVect1, vector<char>);

//function to edit existing contact
//save and read from files

//reorganize functions in order and reflect that order in function prototypes

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
            {
                cin.ignore();//remove newline before jumping into DisplayContacts(), or it won't work properly
                DeleteContact(ContactVector);
            }
                
                break;
                
            default:
                break;
        }
        
        
    }
    while (Choice != 4);
}

void DisplayContacts(const vector<PersonalInformation> &CV)
{
    for (int i = 0; i < CV.size(); i++)
    {
        
        cout << "First Name:   ";
        PrintStringInStructDataVector(CV[i].FirstNameVector);
        
        cout << "Last Name:    ";
        PrintStringInStructDataVector(CV[i].LastNameVector);
        
        cout << "Address:      ";
        PrintStringInStructDataVector(CV[i].AddressVector);
        
        cout << "Phone Number: ";
        PrintStringInStructDataVector(CV[i].PhoneNumberVector);
        
        cout << "Age:          ";
        cout << CV[i].Age;
        
        cout << "\n\n";
        
        usleep(75000);
    }
}

void PrintStringInStructDataVector(const vector<char> &Vector)
{
    for (int i = 0; i < Vector.size(); i++)
    {
        cout << Vector[i];
    }
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
        
        if (Insert != ' ')//only place character in vector if it is not a space - in case of accidental space
            Vector.push_back(Insert);
    }
    
    if (!isnumber(Vector[0]))
        (Vector[0] = toupper(Vector[0]));//if not a number, always capitalize (for first name and last names)
}

void DeleteContact(vector<PersonalInformation> &CV)
{
    vector<char> LastNameToDeleted;
    vector<char> FirstNameToDeleted;
    bool NameFound = false;
    
    DisplayContacts(CV);//display list again
    
    cout << "Type in the last name of the contact you wish to delete";
    cout << "\nLast name: ";
    
    InsertStringInStructDataVector(LastNameToDeleted);
    
    cout << "\nType in the first name of the contact you wish to delete";
    cout << "\nLast name: ";
    
    InsertStringInStructDataVector(FirstNameToDeleted);
    
    for (int i = 0; i<CV.size() && NameFound == false; i++)//find position of name
    {
        if (NamesSame(CV[i].LastNameVector, LastNameToDeleted, CV[i].FirstNameVector, FirstNameToDeleted))
        {
            NameFound = true;
            
            //print this contact and ask if they want to delete it for sure
            
            CV.erase(CV.begin() + i);
        }
    }
    
    if (NameFound == false)
    {
        cout << "\n";
        PrintStringInStructDataVector(FirstNameToDeleted);
        cout << " ";
        PrintStringInStructDataVector(LastNameToDeleted);
        cout << " was not found.";
    }
    
    else
    {
        cout << "\n";
        PrintStringInStructDataVector(FirstNameToDeleted);
        cout << " ";
        PrintStringInStructDataVector(LastNameToDeleted);
        cout << " was deleted.";
    }
}

void SortVector(vector<PersonalInformation> &CV)//not my code - bubble sort
{
    bool SwapsMade = true;
    
    while(SwapsMade)
    {
        SwapsMade = false;
        
        for (int i = 0; i < CV.size()-1; i++)
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
    //checks to see which last name comes first
    
    for (int i = 0; LastNameVect1[i] || LastNameVect2[i]; ++i)//go until you get to the end of the larger name
    {
        if(toupper(LastNameVect1[i]) < toupper(LastNameVect2[i]))//make all uppercase to check for order
            return true;
        
        if(toupper(LastNameVect1[i]) > toupper(LastNameVect2[i]))
            return false;
    }
    
    //if both last names are the same, it then uses the first name
    
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

bool NamesSame(vector<char> LastNameVect1, vector<char> LastNameVect2, vector<char> FirstNameVect1, vector<char> FirstNameVect2)
{
    //code copied from NamesInOrder and modified
    
    for (int i = 0; LastNameVect1[i] || LastNameVect2[i]; ++i)//go until you get to the end of the larger name
    {
        if(toupper(LastNameVect1[i]) == toupper(LastNameVect2[i]))//make all uppercase to check for order
        {
            for (int i = 0; FirstNameVect1[i] || FirstNameVect2[i]; ++i)//go until you get to the end of the larger name
            {
                if(toupper(FirstNameVect1[i]) == toupper(FirstNameVect2[i]))
                    return true;//if first and last name are the same, then return true
            }
        }
    }

    return false;
}
