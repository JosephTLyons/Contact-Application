#include <iostream>   //for input/output stream

#include <ctype.h>    //for toupper function
#include <ctime>      //for time and date functions
#include <fstream>    //for reading from and saving to files
#include <string.h>   //for strcat function in pathway commands
#include <sys/stat.h> //for mkdir functions
#include <unistd.h>   //for usleep functions
#include <vector>     //for using vectors

using namespace std;

struct PersonalInformation
{
    vector <char> FirstNameVector;
    vector <char> LastNameVector;
    vector <char> AddressVector;
    vector <char> PhoneNumberVector;
    
    /* NEW DATA MEMBERS FOR THIS BRANCH */
    
    vector <char> DateOfBirth;

    int MonthBorn;
    int DayBorn;
    int YearBorn;
    
    int CurrentAge;
    
    vector <char> Age;//delete later on - and in clear
};

void MainMenu();

/* Main Menu Functions */

void DisplayContacts(const vector <PersonalInformation> &CV);
void AddContact(vector <PersonalInformation> &CV, const char Path[]);
void EditExistingContact(vector <PersonalInformation> &Vector, const char Path[]);
void DeleteContact(vector <PersonalInformation> &CV, const char Path[]);
void DeleteAllContacts(vector <PersonalInformation> &Vector, const char Path[]);

/* Functions for Reading and Writing From Keyboard and Files */

void PrintStringInStructDataVectorToFile(const vector <char> &Vector, ofstream &FileOut);
void PrintStringInStructDataVectorToScreen(const vector <char> &Vector);
void InsertStringInStructDataVectorFromFile(vector <char> &Vector, ifstream &FileIn);
void InsertStringInStructDataVectorFromKeyboard(vector <char> &Vector);

/* Sorting Functions */

void SortVector(vector <PersonalInformation> &CV);
bool NamesInOrder(vector <char> LastNameVect1, vector <char> LastNameVect2, vector <char> FirstNameVect1, vector <char>
                  FirstNameVect2);

/* Miscellaneous Functions */

void RebuildContactBook(vector <PersonalInformation> &CV, const char Path[]);
void CreateFolderAndTextFile(char FullPath[]);
bool EmptyFileChecker(const char Path[]);
bool EndOfFileChecker(ifstream &FileIn);
void ClearDataVectorsFromStructure(PersonalInformation &X);

/* Functions for Saving */

void SaveContactBook(vector <PersonalInformation> &CV, const char Path[]);
string Date();


int BirthDayInput(PersonalInformation & TempPersonalInfoHolder);
int CalculateCurrentAge(PersonalInformation & TempPersonalInfoHolder, int & MonthBorn, int & DayBorn, int & YearBorn);//DELETE WHEN DONE, JUST FOR TESTING;
int CalculateDayNumberFromMonthAndDay(const int & BirthMonth, const int & BirthDay, const int & CurrentYear);
void StoreDateOfBirthInVector(PersonalInformation & PersonalInformationVector);

/*
 -----------------------------BUGS AND FIXES------------------------------
 
 how big to make array holding pathway? - any way to use vector for this field?
 
 organize latest funtions and function prototypes into the other organized ones
 delete un-needed struct data members when done - Current Age being used
 
 support to just type in newlines to skip birthday, instead of using 0
 
 calculate current age each time contacts are displayed
 fix all other functions like editing etc
 
 ---------------------------NEW FEATURES TO ADD---------------------------
 
 dynamic birthdays?  Enter in birthday and display current age?
 ways to exit main menu functions - type "Q" to leave - then if statement with "return/break"
 enhance loop in delete contact function?
 -support to type in multiple numbers, separated by spaces, to delete a bunch at once
 
*/

int main()
{
    //BirthDayInput();//DELETE WHEN DONE, JUST FOR TESTING;
    MainMenu();
}

void MainMenu()
{
    vector <PersonalInformation> ContactVector;
    static int MainMenuCounter = 0;
    int Choice;
    char FullPath[180] = {0};
    
    CreateFolderAndTextFile(FullPath);//creates The Lyons' Den Labs folder in Application Support folder in Library
    
    if(EmptyFileChecker(FullPath))
        RebuildContactBook(ContactVector, FullPath);
    
    do
    {
        if (MainMenuCounter++ > 0)//skip this set of commands for the first time in the menu, enter every time after
        {
            cout << "Press enter to go back to main menu: ";
            cin.ignore();//pause the program, wait for user to press enter
            
            cout << "\n======================\n";
        }
        
        cout << "(1) Display List";
        cout << "\n(2) Add Contact";
        cout << "\n(3) Edit Existing Contact";
        cout << "\n(4) Delete Contact";
        cout << "\n(5) Delete All Contacts";
        cout << "\n(6) Exit";
        
        cout << "\n\nChoice: ";
        
        cin >> Choice;
        cin.ignore();
        
        cout << "\n";
        
        switch (Choice)
        {
            case 1:
            {
                DisplayContacts(ContactVector);
                break;
            }
                
            case 2:
            {
                AddContact(ContactVector, FullPath);
                break;
            }
                
            case 3:
            {
                EditExistingContact(ContactVector, FullPath);
                break;
            }
                
            case 4:
            {
                DeleteContact(ContactVector, FullPath);
                break;
            }
                
            case 5:
            {
                DeleteAllContacts(ContactVector, FullPath);
                break;
            }
                
            default:
                break;
        }
    }
    while (Choice != 6);
}

void DisplayContacts(const vector<PersonalInformation> &CV)
{
    cout << "======================\n\n";
    
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
        
        cout << "Birthday:       ";
        PrintStringInStructDataVectorToScreen(CV[i].DateOfBirth);
        
        /* ONLY DISPLAY CURRENT AGE IF N/A ISN'T IN DATEOFBIRTH FIELD */
        
        if (CV[i].DateOfBirth[0] != 'N')
        {
            if (CV[i].DateOfBirth[1] != '/')
            {
                if (CV[i].DateOfBirth[2] != 'A')
                {
                    cout << "Current Age:    ";
                    cout << CV[i].CurrentAge;
                }
            }
        }
        
        cout << "\n\n";
        
        usleep(60000);//fine tune this maybe
    }
    
    if (CV.size() == 0)
        cout << "Contact Book is empty.\n\n";
    
    cout << "======================\n\n";
}

void AddContact(vector <PersonalInformation> &CV, const char Path[])
{
    PersonalInformation Temporary;//temporary holding spot for input, used to store in vector
    char UserChoice;
    
    while (toupper(UserChoice) != 'N' && toupper(UserChoice) != 'Q')
    {
        cout << "Enter First Name:   ";
        InsertStringInStructDataVectorFromKeyboard(Temporary.FirstNameVector);
        
        cout << "Enter Last Name:    ";
        InsertStringInStructDataVectorFromKeyboard(Temporary.LastNameVector);
        
        cout << "Enter Address:      ";
        InsertStringInStructDataVectorFromKeyboard(Temporary.AddressVector);
        
        cout << "Enter Phone Number: ";
        InsertStringInStructDataVectorFromKeyboard(Temporary.PhoneNumberVector);
        
        cout << "Enter Birthday:";
        
        Temporary.CurrentAge = BirthDayInput(Temporary);
    
        CV.push_back(Temporary);//store Temp in ContactVector Vector
        
        ClearDataVectorsFromStructure(Temporary);
        
        if (CV.size() > 1)//don't go into sort function if only one name is in vector
            SortVector(CV);
        
        SaveContactBook(CV, Path);//save settings after adding a contact and sorting
        
        cout << "\nAdd another contact? Y/N: ";
        cin >> UserChoice;
        
        if (toupper(UserChoice) == 'Y')//dont cin.ignore() if user doesn't repeat loop, used to keep main from pausing too many times
            cin.ignore();//clear newline from cin >> statement above
        
        cout << "\n";
    }
    
    cin.ignore();//removes 1 newline at the end of this function - needed for main loop to work correctly
}

void EditExistingContact(vector <PersonalInformation> &Vector, const char Path[])
{
    int ContactNumberToEdit;
    char FieldToEdit = 0;
    
    DisplayContacts(Vector);
    
    cout << "Which contact would you like to edit: ";
    cin >> ContactNumberToEdit;
    cin.ignore();//remove newline left over from cin >> statement above
    
    ContactNumberToEdit--;//decrement value here to work with vector/array notation
    
    if (ContactNumberToEdit < Vector.size())//error will occur if tries to erase number outside of vector bound
    {
        cout << "\n\nContact you wish to edit: ";
        
        PrintStringInStructDataVectorToScreen(Vector[ContactNumberToEdit].FirstNameVector);
        
        cout << "\nPress enter to skip editing a field.";
        cout << "\nPress \"Y\" + enter to edit a field.";
        
        cout << "\n\n======================\n\n";
        
        cout << "Original First Name:   ";
        PrintStringInStructDataVectorToScreen(Vector[ContactNumberToEdit].FirstNameVector);
        
        cout << "Edit Field?: ";
        cin.get(FieldToEdit);//using cin.get() so that newlines are stored
        
        if (toupper(FieldToEdit) == 'Y')
        {
            cin.ignore();//clear left over newline in input buffer
            
            Vector[ContactNumberToEdit].FirstNameVector.clear();
            
            cout << "\nEnter New First Name: ";
            InsertStringInStructDataVectorFromKeyboard(Vector[ContactNumberToEdit].FirstNameVector);
            
            FieldToEdit = 0;//reset back to zero so next if condition isn't automatically met
        }
        
        cout << "\nOriginal Last Name:    ";
        PrintStringInStructDataVectorToScreen(Vector[ContactNumberToEdit].LastNameVector);
        
        cout << "Edit Field?: ";
        cin.get(FieldToEdit);//using cin.get() so that newlines are stored
        
        if (toupper(FieldToEdit) == 'Y')
        {
            cin.ignore();//clear left over newline in input buffer
            
            Vector[ContactNumberToEdit].LastNameVector.clear();
            
            cout << "\nEnter New Last Name: ";
            InsertStringInStructDataVectorFromKeyboard(Vector[ContactNumberToEdit].LastNameVector);
            
            FieldToEdit = 0;//reset back to zero so next if condition isn't automatically met
        }
        
        cout << "\nOriginal Address:      ";
        PrintStringInStructDataVectorToScreen(Vector[ContactNumberToEdit].AddressVector);
        
        cout << "Edit Field?: ";
        cin.get(FieldToEdit);//using cin.get() so that newlines are stored
        
        if (toupper(FieldToEdit) == 'Y')
        {
            cin.ignore();//clear left over newline in input buffer
            
            Vector[ContactNumberToEdit].AddressVector.clear();
            
            cout << "\nEnter New Address: ";
            InsertStringInStructDataVectorFromKeyboard(Vector[ContactNumberToEdit].AddressVector);
            
            FieldToEdit = 0;//reset back to zero so next if condition isn't automatically met
        }
        
        cout << "\nOriginal Phone Number: ";
        PrintStringInStructDataVectorToScreen(Vector[ContactNumberToEdit].PhoneNumberVector);
        
        cout << "Edit Field?: ";
        cin.get(FieldToEdit);//using cin.get() so that newlines are stored
        
        if (toupper(FieldToEdit) == 'Y')
        {
            cin.ignore();//clear left over newline in input buffer
            
            Vector[ContactNumberToEdit].PhoneNumberVector.clear();
            
            cout << "\nEnter New Phone Number: ";
            InsertStringInStructDataVectorFromKeyboard(Vector[ContactNumberToEdit].PhoneNumberVector);
            
            FieldToEdit = 0;//reset back to zero so next if condition isn't automatically met
        }
        
        cout << "\nOriginal Age:          ";
        PrintStringInStructDataVectorToScreen(Vector[ContactNumberToEdit].Age);
        
        cout << "Edit Field?: ";
        cin.get(FieldToEdit);//using cin.get() so that newlines are stored
        
        if (toupper(FieldToEdit) == 'Y')
        {
            cin.ignore();//clear left over newline in input buffer
            
            Vector[ContactNumberToEdit].Age.clear();
            
            cout << "\nEnter New Age: ";
            InsertStringInStructDataVectorFromKeyboard(Vector[ContactNumberToEdit].Age);
            
            FieldToEdit = 0;//reset back to zero so next if condition isn't automatically met
        }
        
        cout << "\n\n======================\n\n";
    }
    
    SortVector(Vector);
    SaveContactBook(Vector, Path);
}

void DeleteContact(vector <PersonalInformation> &CV, const char Path[])
{
    int ContactNumberToDelete;
    char ConfirmDelete = 0;
    char DeleteAnotherContactChoice;
    
    do
    {
        DisplayContacts(CV);//display list again
        
        cout << "Type in the number of the contact you wish to delete: ";
        cin >> ContactNumberToDelete;
        
        if (ContactNumberToDelete <= CV.size())//error will occur if tries to erase number outside of vector bound
        {
            ContactNumberToDelete--;//decrement to work with vector/array notation
            
            cout << "\nYou are trying to delete: ";
            
            cout << "\n\n======================\n\n";
            
            cout << "First Name:   ";
            PrintStringInStructDataVectorToScreen(CV[ContactNumberToDelete].FirstNameVector);
            
            cout << "Last Name:    ";
            PrintStringInStructDataVectorToScreen(CV[ContactNumberToDelete].LastNameVector);
            
            cout << "Address:      ";
            PrintStringInStructDataVectorToScreen(CV[ContactNumberToDelete].AddressVector);
            
            cout << "Phone Number: ";
            PrintStringInStructDataVectorToScreen(CV[ContactNumberToDelete].PhoneNumberVector);
            
            cout << "Age:          ";
            PrintStringInStructDataVectorToScreen(CV[ContactNumberToDelete].Age);
            
            cout << "\n======================\n\n";
            
            
            cout << "\nAre you sure you want to delete ";
            
            for (int i = 0; CV[ContactNumberToDelete].FirstNameVector[i] != '\n'; i++)//display name of contact being deleted
            {
                cout << CV[ContactNumberToDelete].FirstNameVector[i];
            }
            
            cout << "? Y/N: ";
            cin >> ConfirmDelete;
            
            if (toupper(ConfirmDelete) == 'Y')
                CV.erase(CV.begin() + ContactNumberToDelete);
        }
        
        else
            cout << "\nNo contact located at this number";
        
        if (toupper(ConfirmDelete) == 'N' && ++ContactNumberToDelete <= CV.size())//increment Contact to work properly with size()function
            cout << "\nNo contact deleted.";//if user chooses to not delete the contact
        
        SaveContactBook(CV, Path);//save settings after deleting a contact
        
        cout << "\n\nDelete another contact? Y/N: ";
        cin >> DeleteAnotherContactChoice;
        cin.ignore();//removes 1 newline at the end of this function - needed for main loop to work correctly
    }
    while (toupper(DeleteAnotherContactChoice) == 'Y');
    
    cout << "\n\n";
}

void DeleteAllContacts(vector <PersonalInformation> &Vector, const char Path[])
{
    vector <char> UserChoice;
    char Insert;
    
    cout << "Are you sure you'd like to delete all contacts? Type \"YES\" to confirm (Must be a capital YES): ";
    
    do
    {
        cin.get(Insert);
        UserChoice.push_back(Insert);
    }
    while (Insert != '\n');
    
    if (UserChoice[0] == 'Y')
    {
        if (UserChoice[1] == 'E')
        {
            if (UserChoice[2] == 'S')
            {
                Vector.clear();
                SaveContactBook(Vector, Path);
                
                cout << "\nAll contacts have been deleted.\n\n";
            }
        }
    }
    
    else
        cout << "\nContacts were not deleted.\n\n";
}

void PrintStringInStructDataVectorToFile(const vector <char> &Vector, ofstream &FileOut)
{
    for (int i = 0; i < Vector.size(); i++)
    {
        FileOut << Vector[i];
    }
}

void PrintStringInStructDataVectorToScreen(const vector <char> &Vector)
{
    for (int i = 0; i < Vector.size(); i++)
    {
        cout << Vector[i];
    }
}

void InsertStringInStructDataVectorFromFile(vector <char> &Vector, ifstream &FileIn)
{
    char Insert = 1;//used for inserting characters into individual struct vectors
    //initialized at 1 to allow while loop to execute
    
    while (Insert != '\n' && Insert != 0)//this character is inserted at the end of the text file
    {
        FileIn.get(Insert);
        
        //if (Insert != '\n')//dont store newlines in text
        
        Vector.push_back(Insert);
    }
}

void InsertStringInStructDataVectorFromKeyboard(vector <char> &Vector)
{
    char Insert = 0;//used for inserting characters into individual struct vectors
    //initialized at 0 to allow while loop to execute
    
    char NameOfEmptyField[] = {"N/A\n"};
    
    while (Insert != '\n')
    {
        cin.get(Insert);//using cin.get, and not cin >>, so it stores the newline in Insert - allows to break out of loop
        
        Vector.push_back(Insert);
    }
    
    if (Vector.size() <= 1)//if theres nothing in vector or just a newline, add "N/A" text in field
    {
        Vector.erase(Vector.begin());//erase newline stored
        
        for (int i = 0; NameOfEmptyField[i] != 0; i++)
        {
            Vector.push_back(NameOfEmptyField[i]);//insert text for "N/A"
        }
    }
    
    while (Vector[0] == ' ')//remove any leading whitespace from vector
        Vector.erase(Vector.begin());//while first element is a space, delete first element
    
    if (!isnumber(Vector[0]))
        (Vector[0] = toupper(Vector[0]));//if not a number, always capitalize (for first name and last names)
}

void SortVector(vector <PersonalInformation> &CV)//my modified bubble sort code I found online
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

bool NamesInOrder(vector <char> LastNameVect1, vector <char> LastNameVect2, vector <char> FirstNameVect1, vector <char> FirstNameVect2)
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

void RebuildContactBook(vector <PersonalInformation> &CV, const char Path[])
{
    PersonalInformation Temporary;
    bool EndOfFile;
    
    ifstream FileIn;
    
    FileIn.open(Path);
    
    if (FileIn.fail())//check to see if file opened
        cout << "Couldn't Open File\n";
    
    for (int i = 0; EndOfFile == false; i++)//2 is temporary - fix condition here to work with getting ALL contacts
    {
        InsertStringInStructDataVectorFromFile(Temporary.FirstNameVector, FileIn);
        
        InsertStringInStructDataVectorFromFile(Temporary.LastNameVector, FileIn);
        
        InsertStringInStructDataVectorFromFile(Temporary.AddressVector, FileIn);
        
        InsertStringInStructDataVectorFromFile(Temporary.PhoneNumberVector, FileIn);
        
        InsertStringInStructDataVectorFromFile(Temporary.DateOfBirth, FileIn);
        
        FileIn >> Temporary.CurrentAge;
        
        FileIn >> Temporary.MonthBorn;
        
        FileIn >> Temporary.DayBorn;
        
        FileIn >> Temporary.YearBorn;
        
        /* AUTOMATICALLY RECALCULATE CURRENT YEAR EVERY TIME LIST IS REBUILT */
        
        CalculateCurrentAge(Temporary, Temporary.MonthBorn, Temporary.DayBorn, Temporary.YearBorn);
    
        CV.push_back(Temporary);
        
        ClearDataVectorsFromStructure(Temporary);
        
        EndOfFile = EndOfFileChecker(FileIn);
    }
    
    FileIn.close();
}

void CreateFolderAndTextFile(char FullPath[])
{
    //optaining pathway on mac / making my custom folder - consider another implementation that uses vector?
    
    const char *HomeAndUserNamePath = getenv("HOME");//get home/username path - finds username
    const char *MorePath = "/Library/Application Support/The Lyons' Den Labs";
    const char *RestOfPath = "/TheLyons'DenContactInformation2.txt";
    
    strcat(FullPath, HomeAndUserNamePath);
    strcat(FullPath, MorePath);
    
    mkdir(FullPath, ACCESSPERMS);//make The Lyons' Den Labs folder
    
    strcat(FullPath, RestOfPath);
    
    //done making folder and obtaining pathway
}

bool EmptyFileChecker(const char Path[])//shouldn't be declaring a new variable, should be passing it in, but that would call for a major rewrite of the menu function and all the function parameters
{
    ifstream FileIn;
    
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

void ClearDataVectorsFromStructure(PersonalInformation &X)
{
    X.FirstNameVector.clear();//clear out all vectors of temporary storage to get ready for next
    X.LastNameVector.clear();
    X.AddressVector.clear();
    X.PhoneNumberVector.clear();
    X.Age.clear();
    X.DateOfBirth.clear();
}

void SaveContactBook(vector <PersonalInformation> &CV, const char Path[])
{
    ofstream FileOut;
    
    FileOut.open(Path);
    
    if (FileOut.fail())//check to see if file opened
        cout << "Couldn't Open File\n";
    
    for (int i = 0; i < CV.size(); i++)
    {
        PrintStringInStructDataVectorToFile(CV[i].FirstNameVector, FileOut);
        
        PrintStringInStructDataVectorToFile(CV[i].LastNameVector, FileOut);
        
        PrintStringInStructDataVectorToFile(CV[i].AddressVector, FileOut);
        
        PrintStringInStructDataVectorToFile(CV[i].PhoneNumberVector, FileOut);
        
        PrintStringInStructDataVectorToFile(CV[i].DateOfBirth, FileOut);
        
        FileOut << endl;
        
        FileOut << CV[i].CurrentAge << endl;
        
        FileOut << CV[i].MonthBorn << endl;
        
        FileOut << CV[i].DayBorn<< endl;
        
        FileOut << CV[i].YearBorn;
        
        FileOut << "\n\n";
    }

    FileOut << (char) 0 << endl;//used as a way to mark the end of the document, using 0 because user can't type it
    
    FileOut << "Contacts Last Altered: " << Date() << endl;
    
    FileOut.close();
}

string Date()//not my code here - modified it to display what I want and to read easier
{
    char Time[50];
    
    time_t now = time(NULL);
    strftime(Time, 50, "%D, %I:%M %p", localtime(&now));
    
    return string(Time);
}

int BirthDayInput(PersonalInformation & TempPersonalInfoHolder)
{
    /* USER ENTERS IN CONTACTS BIRTHDAY */
    
    cout << "\n  Enter Month (1 - 12): ";
    cin >> TempPersonalInfoHolder.MonthBorn;
    
    cout << "  Enter Day (1 - 31):   ";
    cin >> TempPersonalInfoHolder.DayBorn;
    
    cout << "  Enter Year (XXXX):    ";
    cin >> TempPersonalInfoHolder.YearBorn;
    
    /* STORE DATE OF BIRTH IN DATEOFBIRTH VECTOR */
    
    StoreDateOfBirthInVector(TempPersonalInfoHolder);
    
    return CalculateCurrentAge(TempPersonalInfoHolder, TempPersonalInfoHolder.MonthBorn, TempPersonalInfoHolder.DayBorn, TempPersonalInfoHolder.YearBorn);
}

int CalculateCurrentAge(PersonalInformation & TempPersonalInfoHolder, int & MonthBorn, int & DayBorn, int & YearBorn)
{
    int DayOfTheYearBirthdayLandsOn = 0;
    int UsersCurrentAge = 0;
    
    char CurrentMonthOfThisYearString[3];//only 2 digits, EX 11 (November), +1 for null
    char CurrentDayOfThisYearString[4];//only 3 digits will ever be here, 365 days is 3 digits long, +1 for null
    char CurrentYearString[5];//only 4 digits will ever be here, EX. 2016 is 4 digits long, +1 for null
    
    int CurrentMonthOfThisYear = 0;
    int CurrentDayOfThisYear = 0;
    int CurrentYear = 0;
    
    time_t now = time(NULL);//Get current time/date
    
    /* GET CURRENT MONTH, CONVERT TO NUMBER, AND STORE IN THE ASSOCIATED INT */
    
    strftime(CurrentMonthOfThisYearString, 3, "%m", localtime(&now));//store month number in string
    
    for (int i = 0; CurrentMonthOfThisYearString[i]; i++)
    {
        CurrentMonthOfThisYear *= 10;
        CurrentMonthOfThisYear += (CurrentMonthOfThisYearString[i] - 48);
    }
    
    /* GET CURRENT DAY OF THIS YEAR, CONVERT TO NUMBER, AND STORE IN THE ASSOCIATED INT */
    
    strftime(CurrentDayOfThisYearString, 4, "%j", localtime(&now));//store day of year in string
    
    for (int i = 0; CurrentDayOfThisYearString[i]; i++)
    {
        CurrentDayOfThisYear *= 10;
        CurrentDayOfThisYear += (CurrentDayOfThisYearString[i] - 48);
    }
    
    /* GET CURRENT YEAR, CONVERT TO NUMBER, AND STORE IN THE ASSOCIATED INT */
    
    strftime(CurrentYearString, 5, "%Y", localtime(&now));//store current year in string
    
    for (int i = 0; CurrentYearString[i]; i++)
    {
        CurrentYear *= 10;
        CurrentYear += (CurrentYearString[i] - 48);
    }
    
    /* CALCULATE WHAT DAY OF THE YEAR THE USERS BIRTHDAY LANDS ON */
    
    DayOfTheYearBirthdayLandsOn = CalculateDayNumberFromMonthAndDay(MonthBorn, DayBorn, CurrentYear);
    
    UsersCurrentAge = CurrentYear - YearBorn;//Obtain age
    
    /* IF USERS BIRTHDAY HASN'T OCCURED THIS YEAR, THEN DECREMENT THEIR AGE BY 1 */
    
    if (CurrentDayOfThisYear < DayOfTheYearBirthdayLandsOn)
        --UsersCurrentAge;
    
    return UsersCurrentAge;
}

int CalculateDayNumberFromMonthAndDay(const int & BirthMonth, const int & BirthDay, const int & CurrentYear)
{
    int DayOfYearThatBirthdayIsOn = 0;
    int DayHolder = 0;
    
    // FUNCTION DOESN'T ACCOUNT FOR LEAP YEARS CURRENTLY - IMPLEMENT LATER
    
    if (BirthMonth >= 1)//January - 31
    {
        DayOfYearThatBirthdayIsOn += DayHolder;
        DayHolder = 31;
    }
    
    if (BirthMonth >= 2)//February - 28/29
    {
        DayOfYearThatBirthdayIsOn += DayHolder;
        DayHolder = 28;
        
        /* CHECK TO SEE IF LEAP YEAR OR NOT */
        
        if (CurrentYear % 4 == 0)
        {
            if (CurrentYear % 100 == 0)
            {
                if (CurrentYear % 400 == 0)
                    DayHolder = 29;
            }
            
            else
                DayHolder = 29;
            
        }
                    
        /* - ALGORITH AB0VE DERIVED FROM
         
         https://support.microsoft.com/en-us/kb/214019
         
         1. If the year is evenly divisible by 4, go to step 2. Otherwise, go to step 5.
         2. If the year is evenly divisible by 100, go to step 3. Otherwise, go to step 4.
         3. If the year is evenly divisible by 400, go to step 4. Otherwise, go to step 5.
         4. The year is a leap year (it has 366 days).
         5. The year is not a leap year (it has 365 days).
         
         */
            
    }
    
    if (BirthMonth >= 3)//March - 31
    {
        DayOfYearThatBirthdayIsOn += DayHolder;
        DayHolder = 31;
    }
    
    if (BirthMonth >= 4)//April - 30
    {
        DayOfYearThatBirthdayIsOn += DayHolder;
        DayHolder = 30;
    }
    
    if (BirthMonth >= 5)//May - 31
    {
        DayOfYearThatBirthdayIsOn += DayHolder;
        DayHolder = 31;
    }
    
    if (BirthMonth >= 6)//June - 30
    {
        DayOfYearThatBirthdayIsOn += DayHolder;
        DayHolder = 30;
    }
    
    if (BirthMonth >= 7)//July - 31
    {
        DayOfYearThatBirthdayIsOn += DayHolder;
        DayHolder = 31;
    }
    
    if (BirthMonth >= 8)//August - 31
    {
        DayOfYearThatBirthdayIsOn += DayHolder;
        DayHolder = 31;
    }
    
    if (BirthMonth >= 9)//September - 30
    {
        DayOfYearThatBirthdayIsOn += DayHolder;
        DayHolder = 30;
    }
    
    if (BirthMonth >= 10)//October - 31
    {
        DayOfYearThatBirthdayIsOn += DayHolder;
        DayHolder = 31;
    }
    
    if (BirthMonth >= 11)//November - 30
    {
        DayOfYearThatBirthdayIsOn += DayHolder;
        DayHolder = 30;
    }
    
    if (BirthMonth >= 12)//December - 31
    {
        DayOfYearThatBirthdayIsOn += DayHolder;
        DayHolder = 31;
    }
    
    DayOfYearThatBirthdayIsOn += BirthDay;
    
    return DayOfYearThatBirthdayIsOn;
}

void StoreDateOfBirthInVector(PersonalInformation& TempPersonalInfoHolder)
{
    const char *MonthNames[12] = {"January",   "February", "March",    "April",
                                  "May",       "June",     "July",     "August",
                                  "September", "October",  "November", "December"};
    
    int TempMonth = TempPersonalInfoHolder.MonthBorn;
    int TempDay   = TempPersonalInfoHolder.DayBorn;
    int TempYear  = TempPersonalInfoHolder.YearBorn;
    
    char YearArray[5] = {0};//years limited to 4 digits - one day, we will have 5 digit years
    char DayArray[3]  = {0};//days limited to 2 digits - this is ok, will never be larger
    
    /* FIRST CHECK TO SEE IF BIRTHDAY WAS ENTERED - LATER CHANGE THIS TO JUST HITTING ENTER */
    
    if (TempPersonalInfoHolder.MonthBorn == 0)
    {
        if (TempPersonalInfoHolder.DayBorn == 0)
        {
            if (TempPersonalInfoHolder.YearBorn == 0)
            {
                TempPersonalInfoHolder.DateOfBirth.push_back('N');
                TempPersonalInfoHolder.DateOfBirth.push_back('/');
                TempPersonalInfoHolder.DateOfBirth.push_back('A');
                return;
            }
        }
    }
    
    /* INSERT MONTH NAME INTO DATEOFBIRTH VECTOR */
    
    for (int i = 0; MonthNames[TempMonth-1][i]; i++)
    {
        TempPersonalInfoHolder.DateOfBirth.push_back(MonthNames[TempMonth-1][i]);
    }
    
    TempPersonalInfoHolder.DateOfBirth.push_back(' ');
    
    /* STORE DAY IN CHAR ARRAY TO MAKE INSERTION IN DATEOFBIRTH VECTOR EASIER */
    
    for (int i = 1; i >= 0; i--)
    {
        DayArray[i] *= 10;
        DayArray[i] = (TempDay % 10) + 48;//convertion happens here
        TempDay /= 10;
    }
    
    /* INSERT DAY INTO DATEOFBIRTH VECTOR */

    for (int i = 0; DayArray[i]; i++)
        TempPersonalInfoHolder.DateOfBirth.push_back(DayArray[i]);
    
    TempPersonalInfoHolder.DateOfBirth.push_back(',');
    TempPersonalInfoHolder.DateOfBirth.push_back(' ');
    
    /* STORE YEAR IN CHAR ARRAY TO MAKE INSERTION IN DATEOFBIRTH VECTOR EASIER */
    
    for (int i = 3; i >= 0; i--)
    {
        YearArray[i] *= 10;
        YearArray[i] = (TempYear % 10) + 48;//convertion happens here
        TempYear /= 10;
    }
    
    /* INSERT YEAR INTO DATEOFBIRTH VECTOR */
    
    for (int i = 0; YearArray[i]; i++)
        TempPersonalInfoHolder.DateOfBirth.push_back(YearArray[i]);
}