#include <iostream>

#include <ctype.h>//for toupper function
#include <fstream>//for reading from and saving to files
#include <unistd.h>//for usleep function
#include <vector>

using namespace std;

struct PersonalInformation
{
    vector <char> FirstNameVector;
    vector <char> LastNameVector;
    vector <char> AddressVector;
    vector <char> PhoneNumberVector;
    
    short int Age;
};

void RebuildContactBook();
void MainMenu();
void DisplayContacts(const vector<PersonalInformation> &CV);
void PrintStringInStructDataVectorToScreen(const vector<char> &Vector);
void AddContact(vector<PersonalInformation> &CV);
void InsertStringInStructDataVector(vector<char> &Vector);
void DeleteContact(vector<PersonalInformation> &CV);
void SortVector(vector<PersonalInformation> &CV);
bool NamesInOrder(vector<char> LastNameVect1, vector<char> LastNameVect2, vector<char> FirstNameVect1, vector<char>
                  FirstNameVect2);
void SaveContactBook(vector<PersonalInformation> &CV);
void PrintStringInStructDataVectorToFile(const vector<char> &Vector, ofstream &FileOut, const char *Path);
string Date();

//function to edit existing contact
//save and read from files

//reorganize functions in order and reflect that order in function prototypes

int main()
{
    MainMenu();
}

void MainMenu()
{
    vector<PersonalInformation> ContactVector;
    int Choice;
    
    //load list into vector from file
    
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
    
    //SaveContactBook(ContactVector); remove later if program works without it
}

void DisplayContacts(const vector<PersonalInformation> &CV)
{
    for (int i = 0; i < CV.size(); i++)
    {
        cout << "Contact Number: " << i+1;
        cout << "\nFirst Name:     ";
        PrintStringInStructDataVectorToScreen(CV[i].FirstNameVector);
        
        cout << "Last Name:      ";
        PrintStringInStructDataVectorToScreen(CV[i].LastNameVector);
        
        cout << "Address:        ";
        PrintStringInStructDataVectorToScreen(CV[i].AddressVector);
        
        cout << "Phone Number:   ";
        PrintStringInStructDataVectorToScreen(CV[i].PhoneNumberVector);
        
        cout << "Age:            ";
        cout << CV[i].Age;
        
        cout << "\n\n";
        
        usleep(75000);
    }
}

void PrintStringInStructDataVectorToScreen(const vector<char> &Vector)
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
    
    SaveContactBook(CV);//save settings after adding a contact and sorting
}

void InsertStringInStructDataVector(vector<char> &Vector)
{
    char Insert = 0;//used for inserting characters into individual struct vectors
                    //initialized at 0 to allow while loop to execute
    
    while (Insert != '\n')
    {
        cin.get(Insert);//using cin.get, and not cin >>, so it stores the newline in Insert - allows to break out of loop
    
        //figure out way to remove leading whitespace
        
        Vector.push_back(Insert);
    }
    
    if (!isnumber(Vector[0]))
        (Vector[0] = toupper(Vector[0]));//if not a number, always capitalize (for first name and last names)
}

void DeleteContact(vector<PersonalInformation> &CV)
{
    int ContactNumberToDelete;
    //char ConfirmDelete;
    
    DisplayContacts(CV);//display list again
    
    cout << "Enter number of contact you wish to delete: ";
    cin >> ContactNumberToDelete;
    
    //print this contact and ask if they want to delete it for sure
    
    if (ContactNumberToDelete-1 <= CV.size())//error will occur if tries to erase number outside of vector bound
        CV.erase(CV.begin() + (ContactNumberToDelete-1));
    
    SaveContactBook(CV);//save settings after deleting a contact
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

void SaveContactBook(vector<PersonalInformation> &CV)
{
    ofstream FileOut;
    const char *Path = "/Users/josephlyons/Library/Application Support/The Lyons' Den Labs/TheLyons'DenContactInformation2.txt";//code variable for username
    
    FileOut.open(Path);
    
    for (int i = 0; i < CV.size(); i++)
    {
        FileOut << "\nFirst Name:     ";
        PrintStringInStructDataVectorToFile(CV[i].FirstNameVector, FileOut, Path);
        
        FileOut << "Last Name:      ";
        PrintStringInStructDataVectorToFile(CV[i].LastNameVector, FileOut, Path);
        
        FileOut << "Address:        ";
        PrintStringInStructDataVectorToFile(CV[i].AddressVector, FileOut, Path);
        
        FileOut << "Phone Number:   ";
        PrintStringInStructDataVectorToFile(CV[i].PhoneNumberVector, FileOut, Path);
        
        FileOut << "Age:            ";
        FileOut << CV[i].Age;
        
        FileOut << "\n\n";
    }

    FileOut << (char) 0 << endl;
    
    FileOut << "Contacts Last Altered: " << Date() << endl;
    
    FileOut.close();
}

void PrintStringInStructDataVectorToFile(const vector<char> &Vector, ofstream &FileOut, const char *Path)
{
    for (int i = 0; i < Vector.size(); i++)
    {
        FileOut << Vector[i];
    }
}

string Date()//not my code here - just modified it to read easier
{
    char Time[50];
    time_t now = time(NULL);
    strftime(Time, 50, "%b, %d, %Y", localtime(&now)); //short month name
    return string(Time);
}