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

void RebuildContactBook(vector<PersonalInformation> &CV);
bool EmptyFileChecker();
bool EndOfFileChecker(ifstream &FileIn);
void MainMenu();
void DisplayContacts(const vector<PersonalInformation> &CV);
void PrintStringInStructDataVectorToScreen(const vector<char> &Vector);
void AddContact(vector<PersonalInformation> &CV);
void InsertStringInStructDataVectorFromKeyboard(vector<char> &Vector);
void InsertStringInStructDataVectorFromFile(vector<char> &Vector, ifstream &FileIn);
void DeleteContact(vector<PersonalInformation> &CV);
void SortVector(vector<PersonalInformation> &CV);
bool NamesInOrder(vector<char> LastNameVect1, vector<char> LastNameVect2, vector<char> FirstNameVect1, vector<char>
                  FirstNameVect2);
void SaveContactBook(vector<PersonalInformation> &CV);
void PrintStringInStructDataVectorToFile(const vector<char> &Vector, ofstream &FileOut);
string Date();

//function to edit existing contact
//save and read from files

//reorganize functions in order and reflect that order in function prototypes
//add lines between functions for visual organization and cin.ignore statements to pause befor returning to menu

//find bug that occurs when entering multiple names in a row in (5+ names)
//bug that doesn't allow you to enter add contact function again after leaving the add function once

//in save function, store "no data entered" in blank fields, or a non-printable character, and use that when reading in
//from the file so that program knows to skip that field

//code function that reads from file to work with blank spaces

//consider making clearPersonalinformationStructure function - used twice

int main()
{
    MainMenu();
}

void MainMenu()
{
    vector<PersonalInformation> ContactVector;
    
    int Choice;
    
    if(EmptyFileChecker())
        RebuildContactBook(ContactVector);
    
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

bool EmptyFileChecker()//shouldn't be declaring a new variable, should be passing it in, but that would call for a major rewrite of the menu function and all the function parameters
{
    ifstream FileIn;
    
    const char *Path = "/Users/josephlyons/Library/Application Support/The Lyons' Den Labs/TheLyons'DenContactInformation2.txt";//code variable for username
    
    FileIn.open(Path);
    
    if (FileIn.fail())
    {
        FileIn.close();
        return false;
    }
    
    else if (FileIn.eof())//return false if file doesnt exist or if file is empty//replace with EndOfFile custom funct??
    {
        FileIn.close();
        return false;
    }
    
    else
    {   FileIn.close();
        return true;
    }
}


void RebuildContactBook(vector<PersonalInformation> &CV)
{
    PersonalInformation Temporary;
    bool EndOfFile;
    
    ifstream FileIn;
    
    const char *Path = "/Users/josephlyons/Library/Application Support/The Lyons' Den Labs/TheLyons'DenContactInformation2.txt";//code variable for username
    
    FileIn.open(Path);
    
    if (FileIn.fail())//check to see if file opened
        cout << "Couldn't Open File\n";
    
    for (int i = 0; EndOfFile == false; i++)//2 is temporary - fix condition here to work with getting ALL contacts
    {
        InsertStringInStructDataVectorFromFile(Temporary.FirstNameVector, FileIn);
        
        InsertStringInStructDataVectorFromFile(Temporary.LastNameVector, FileIn);
        
        InsertStringInStructDataVectorFromFile(Temporary.AddressVector, FileIn);
        
        InsertStringInStructDataVectorFromFile(Temporary.PhoneNumberVector, FileIn);
        
        FileIn >> Temporary.Age;
        
        CV.push_back(Temporary);
        
        Temporary.FirstNameVector.clear();//clear out all vectors of temporary storage to get ready for next
        Temporary.LastNameVector.clear();
        Temporary.AddressVector.clear();
        Temporary.PhoneNumberVector.clear();
        
        EndOfFile = EndOfFileChecker(FileIn);
    }
    
    FileIn.close();
}

bool EndOfFileChecker(ifstream &FileIn)//remove superfluous newlines between contacts and after last contactnew
                                       //check for end of file (I used 0)
{
    char Temporary;
    
    do
    {
        FileIn.get(Temporary);
        
        if (Temporary == 0)
            return true;
        
        if (Temporary != '\n' && Temporary != 0)//this if statement is used to place back first letter
                                                //otherwise, you risk losing first letter if not EndOfFile
            FileIn.putback(Temporary);
    }
    while (Temporary == '\n');
    
    return false;
}

void InsertStringInStructDataVectorFromFile(vector <char> &Vector, ifstream &FileIn)
{
    char Insert = 1;//used for inserting characters into individual struct vectors
    //initialized at 1 to allow while loop to execute
    
    while (Insert != '\n' && Insert != 0)//this character is inserted at the end of the text file
    {
        FileIn.get(Insert);
        
        //figure out way to remove leading whitespace
        
        //if (Insert != '\n')//dont store newlines in text
        
        Vector.push_back(Insert);
    }
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
        
        usleep(90000);//fine tune this maybe
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
    
    while (toupper(UserChoice) != 'N')
    {
        cout << "Enter First Name:   ";
        InsertStringInStructDataVectorFromKeyboard(Temp.FirstNameVector);
        
        cout << "Enter Last Name:    ";
        InsertStringInStructDataVectorFromKeyboard(Temp.LastNameVector);
        
        cout << "Enter Address:      ";
        InsertStringInStructDataVectorFromKeyboard(Temp.AddressVector);
        
        cout << "Enter Phone Number: ";
        InsertStringInStructDataVectorFromKeyboard(Temp.PhoneNumberVector);
        
        cout << "Enter Age:          ";
        cin >> Temp.Age;
        
        CV.push_back(Temp);//store Temp in ContactVector Vector
        
        Temp.FirstNameVector.clear();//clear out all vectors of temporary storage to get ready for next
        Temp.LastNameVector.clear();
        Temp.AddressVector.clear();
        Temp.PhoneNumberVector.clear();
        
        if (CV.size() > 1)//don't go into sort function if only one name is in vector
            SortVector(CV);
        
        SaveContactBook(CV);//save settings after adding a contact and sorting
        
        cout << "\nAdd another contact? Y/N: ";
        cin >> UserChoice;
        cin.ignore();//removes newline left in input buffer after last cin >> statement
        cout << "\n";
    }
}

void InsertStringInStructDataVectorFromKeyboard(vector<char> &Vector)
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
    char ConfirmDelete;
    
    DisplayContacts(CV);//display list again
    
    cout << "Enter number of contact you wish to delete: ";
    cin >> ContactNumberToDelete;
    ContactNumberToDelete--;//decrement value here to work with vector/array notation
    
    cout << "You are trying to delete: \n\n";
    
    PrintStringInStructDataVectorToScreen(CV[ContactNumberToDelete].FirstNameVector);
    PrintStringInStructDataVectorToScreen(CV[ContactNumberToDelete].LastNameVector);
    PrintStringInStructDataVectorToScreen(CV[ContactNumberToDelete].AddressVector);
    PrintStringInStructDataVectorToScreen(CV[ContactNumberToDelete].PhoneNumberVector);
    cout << CV[ContactNumberToDelete].Age << "\n";
    
    cout << "\nAre you sure you want to delete this contact? Y/N: ";
    cin >> ConfirmDelete;
    
    if (ContactNumberToDelete <= CV.size())//error will occur if tries to erase number outside of vector bound
    {
        if (toupper(ConfirmDelete) == 'Y')
            CV.erase(CV.begin() + ContactNumberToDelete);
    }
    
    if (toupper(ConfirmDelete) != 'Y')
        cout << "Contact wasn't deleted.";//if user chooses to not delete the contact
    
    cout << "\n\n";
    
    SaveContactBook(CV);//save settings after deleting a contact
}

void SortVector(vector<PersonalInformation> &CV)//my modified bubble sort code I found online
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
    
    for (int i = 0; LastNameVect1[i] && LastNameVect2[i]; ++i)//go until you get to the end of the larger name
    {
        if(toupper(LastNameVect1[i]) < toupper(LastNameVect2[i]))//make all uppercase to check for order
            return true;
        
        if(toupper(LastNameVect1[i]) > toupper(LastNameVect2[i]))
            return false;
    }
    
    //if both last names are the same, it then uses the first name
    
    for (int i = 0; FirstNameVect1[i] && FirstNameVect2[i]; ++i)//go until you get to the end of the larger name
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
    
    if (FileOut.fail())//check to see if file opened
        cout << "Couldn't Open File\n";
    
    for (int i = 0; i < CV.size(); i++)
    {
        PrintStringInStructDataVectorToFile(CV[i].FirstNameVector, FileOut);
        
        PrintStringInStructDataVectorToFile(CV[i].LastNameVector, FileOut);
        
        PrintStringInStructDataVectorToFile(CV[i].AddressVector, FileOut);
        
        PrintStringInStructDataVectorToFile(CV[i].PhoneNumberVector, FileOut);

        FileOut << CV[i].Age;
        
        FileOut << "\n\n";
    }

    FileOut << (char) 0 << endl;//used as a way to mark the end of the document, using 0 because user can type it
    
    FileOut << "Contacts Last Altered: " << Date() << endl;
    
    FileOut.close();
}

void PrintStringInStructDataVectorToFile(const vector<char> &Vector, ofstream &FileOut)
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