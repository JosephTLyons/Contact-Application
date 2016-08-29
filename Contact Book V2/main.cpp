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
    vector <char> DateOfBirth;
    int MonthBorn;
    int DayBorn;
    int YearBorn;
    int CurrentAge;
    short int BirthdayIsInXDays;
};

/* MAIN MENU FUNCTIONS */

void DisplayContacts(const vector<PersonalInformation> &ContactVect, const int &DisplaySpeed);
void AddContact(vector <PersonalInformation> &ContactVect);
void EditExistingContact(vector <PersonalInformation> &ContactVect, const int &DisplaySpeed);
void DeleteContact(vector <PersonalInformation> &ContactVect, const int &DisplaySpeed);
void DeleteAllContacts(vector <PersonalInformation> &ContactVect);
void DisplaySettingsMenu(const vector <PersonalInformation> &ContactVect, int &DisplaySpeed, int &SpeedSelectionChoice, bool &EncryptionMode);

/* USER SETTINGS FUNCTIONS */

void EncryptionOnOffSetting(bool &EncryptionMode);
void ScrollSpeedSettingsAndUserInput(const vector <PersonalInformation> &ContactVect, int &DisplaySpeed, int &SpeedSelectionChoice);
void ObtainSpeedSettingNumericalValues(int &DisplaySpeed, const int &SpeedSelectionChoice);

/* FUNCTIONS FROM READING AND WRITING FROM FILES AND FROM KEYBOARD */

void PrintVectorToFile(const vector <char> &ContactVect, ofstream &FileOut, const bool &EncryptionMode);
void PrintVectorToScreen(const vector <char> &ContactVect);
void InsertStringInVectorFromFile(vector <char> &ContactVect, ifstream &FileIn, const bool &EncryptionMode);
void InsertStringDataVectorFromKeyboard(vector <char> &ContactVect);

/* SORTING FUNCTIONS */

void SortContactVector(vector <PersonalInformation> &ContactVect);
bool NamesInOrder(const vector <char> &LastNameVect1, const vector <char> &LastNameVect2, const vector <char> &FirstNameVect1, const vector <char> &FirstNameVect2);

/* MISCELLANEOUS FUNCTIONS */

void RebuildContactBook(vector <PersonalInformation> &ContactVect, const char Path[], int &SpeedSelectionChoice, bool &EncryptionMode);
void CreateFolderAndTextFile(char FullPath[]);
bool CheckIfFileExistsAndContainsInformation(const char Path[]);
void ClearDataVectorsFromStructure(PersonalInformation &TemporaryStorage);

/* FUNCTIONS FOR DYNAMIC AGE/BIRTHDAY */
 
int BirthDayInput(PersonalInformation &TempPersonalInfoHolder);
int CalculateCurrentAge(PersonalInformation &TempPersonalInfoHolder, const int &MonthBorn, const int &DayBorn, const int &YearBorn);
int CalculateDayNumberFromMonthAndDay(const int &BirthMonth, const int &BirthDay, const int &CurrentYear);
void StoreDateOfBirthInVector(PersonalInformation &TempPersonalInfoHolder);

/* FUNCTIONS FOR ENCRYPTION/DECRYPTION */

char EncryptDecryptChar(char Input, const bool &EncryptionMode);
int EncryptDecryptInt(int Input, const bool &EncryptionMode);

/* FUNCTIONS FOR SAVING */

void SaveContactBookAndSettings(const vector <PersonalInformation> &ContactVect, const char Path[], const int &SpeedSelectionChoice, const bool &EncryptionMode);
string ObtainDateAndTime();

/*
 -----------------------------BUGS AND FIXES------------------------------
 REFACTOR CODE - make easier to read
 
 add comments
 rename other formal parameters
 rename objects declared in functions
 ------
 
 figure out how to remove extra newline between contacts with N/A for their birthdays
 
 how big to make array holding pathway? - any way to use vector for this field?

 support to just type in newlines to skip birthday, instead of using 0 - use of cin.get() and chars, not int
 --use temp char variables in birthday input, then convert them to numbers, so I dont have to change the data
 --members from int to char, which would be a lot of extra work
 
 bound checking on birthday entry
 -no months greater than 12
 -no days greater than 31
 
 work on optimizing code by changing int to short int or using characters - in functions and in struct
 
 bring the boundchecking (no contact at this location) over from deleting function to edit function
 
 change birthday reminder from struct data member to variable in display function that holds number
 and displays to screen, being overwrtten each time - maybe
 
 ---------------------------NEW FEATURES TO ADD---------------------------
 password protect the encryption by using a password and cycling the letters of the password
    then going back to the beginning of that password and doing it again until its done
 
 expand more in the user settings
 
 ways to exit main menu functions - type "Q" to leave - then if statement with "return/break"
 enhance loop in delete contact function?
 -support to type in multiple numbers, separated by spaces, to delete a bunch at once
 support to let user know when a person's birthday is, up to 7 days before it comes, and
    exactly how many days it is until their birthday
 
 search for contact function
*/

// FIX ALL VECTOR CLEARS TO VECTOR SWAP, TO DEALLOCATE MEMORY AND GET IT BACK, SEARCH FOR "CLEAR" TO FIND OCCURANCES

int main()
{
    vector <PersonalInformation> ContactVector;//holds all contacts
    static int MainMenuPauseCounter = 0;//pauses main menu and waits for user to press enter
    char FullPath[180] = {0};//holds the pathway to the .txt file that saves the information
    int SwitchChoice;//
    int DisplaySpeed;
    int SpeedSelectionChoice = 2;//default medium speed setting / when program is first ran
    bool EncryptionMode;
    //-------------------
    
    /* CREATE THE LYONS' DEN LABS FOLDER AND TEXT FILE IN APPLICATOIN SUPPORT FOLDER IN LIBRARY */
    
    CreateFolderAndTextFile(FullPath);
    
    /* CHECK TO SEE IF FILE EXISTS AND HAS INFORMATION IN IT, IF SO, REBUILD THE LIST */
    
    if(CheckIfFileExistsAndContainsInformation(FullPath))
    {
        RebuildContactBook(ContactVector, FullPath, SpeedSelectionChoice, EncryptionMode);//restore contacts
        ObtainSpeedSettingNumericalValues(DisplaySpeed, SpeedSelectionChoice);//restore user settings
    }
    
    do
    {
        if (MainMenuPauseCounter++ > 0)//pauses the program before displaying the main menu again on second time and after
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
        cout << "\n(6) Settings and Configuration";
        cout << "\n(7) Exit";
        
        cout << "\n\nChoice: ";
        
        cin >> SwitchChoice;
        cin.ignore();//ignore newline in buffer after cin >> statement
        
        cout << "\n";
        
        switch (SwitchChoice)
        {
            case 1:
            {
                DisplayContacts(ContactVector, DisplaySpeed);
                break;
            }
                
            case 2:
            {
                AddContact(ContactVector);
                SaveContactBookAndSettings(ContactVector, FullPath, SpeedSelectionChoice, EncryptionMode);
                break;
            }
                
            case 3:
            {
                EditExistingContact(ContactVector, DisplaySpeed);
                SaveContactBookAndSettings(ContactVector, FullPath, SpeedSelectionChoice, EncryptionMode);
                break;
            }
                
            case 4:
            {
                DeleteContact(ContactVector, DisplaySpeed);
                SaveContactBookAndSettings(ContactVector, FullPath, SpeedSelectionChoice, EncryptionMode);
                break;
            }
                
            case 5:
            {
                DeleteAllContacts(ContactVector);
                SaveContactBookAndSettings(ContactVector, FullPath, SpeedSelectionChoice, EncryptionMode);
                break;
            }
                
            case 6:
            {
                DisplaySettingsMenu(ContactVector, DisplaySpeed, SpeedSelectionChoice, EncryptionMode);
                SaveContactBookAndSettings(ContactVector, FullPath, SpeedSelectionChoice, EncryptionMode);
                break;
            }
                
            default:
                break;
        }
    }
    while (SwitchChoice != 7);
}

void DisplayContacts(const vector<PersonalInformation> &ContactVect, const int &DisplaySpeed)//not cleaned up
{
    cout << "======================\n\n";
    
    for (int i = 0; i < ContactVect.size(); i++)
    {
        cout << "Contact Number: " << i+1;
        cout << "\nFirst Name:     ";
        PrintVectorToScreen(ContactVect[i].FirstNameVector);
        
        cout << "Last Name:      ";
        PrintVectorToScreen(ContactVect[i].LastNameVector);
        
        cout << "Address:        ";
        PrintVectorToScreen(ContactVect[i].AddressVector);
        
        cout << "Phone Number:   ";
        PrintVectorToScreen(ContactVect[i].PhoneNumberVector);
        
        cout << "Date Of Birth:  ";
        PrintVectorToScreen(ContactVect[i].DateOfBirth);
        
        /* ONLY DISPLAY CURRENT AGE IF N/A ISN'T IN DATEOFBIRTH FIELD */
        
        if (ContactVect[i].DateOfBirth[0] != 'N')
        {
            if (ContactVect[i].DateOfBirth[1] != '/')
            {
                if (ContactVect[i].DateOfBirth[2] != 'A')
                {
                    cout << "Current Age:    ";
                    cout << ContactVect[i].CurrentAge;
                }
            }
        }
        
        /* IF BIRTHDAY IS LESS THAN 7 DAYS AWAY, DISPLAY THAT INFORMATION TO THE SCREEEN */
        
        if (ContactVect[i].BirthdayIsInXDays >= 0 && ContactVect[i].BirthdayIsInXDays <= 7)
            cout << "\n*BIRTHDAY IS IN " << ContactVect[i].BirthdayIsInXDays << " DAYS*";
        
        cout << "\n\n";
        
        usleep(DisplaySpeed);
    }
    
    /* IF THERE ARE NO CONTACTS, DISPLAY CONTACT BOOK IS EMPTY */
    
    if (ContactVect.size() == 0)
        cout << "Contact Book is empty.\n\n";
    
    cout << "======================\n\n";
}

void AddContact(vector <PersonalInformation> &ContactVect)//not cleaned up
{
    PersonalInformation Temporary;//temporary holding spot for input, used to store in vector
    char UserChoice;
    
    while (toupper(UserChoice) != 'N' && toupper(UserChoice) != 'Q')
    {
        cout << "Enter First Name:   ";
        InsertStringDataVectorFromKeyboard(Temporary.FirstNameVector);
        
        cout << "Enter Last Name:    ";
        InsertStringDataVectorFromKeyboard(Temporary.LastNameVector);
        
        cout << "Enter Address:      ";
        InsertStringDataVectorFromKeyboard(Temporary.AddressVector);
        
        cout << "Enter Phone Number: ";
        InsertStringDataVectorFromKeyboard(Temporary.PhoneNumberVector);
        
        cout << "Enter Birthday:";
        
        Temporary.CurrentAge = BirthDayInput(Temporary);
    
        ContactVect.push_back(Temporary);//store Temp in ContactVector Vector
        
        ClearDataVectorsFromStructure(Temporary);
        
        if (ContactVect.size() > 1)//don't go into sort function if only one name is in vector
            SortContactVector(ContactVect);
        
        cout << "\nAdd another contact? Y/N: ";
        cin >> UserChoice;
        
        if (toupper(UserChoice) == 'Y')//dont cin.ignore() if user doesn't repeat loop, used to keep main from pausing too many times
            cin.ignore();//clear newline from cin >> statement above
        
        cout << "\n";
    }
    
    cin.ignore();//removes 1 newline at the end of this function - needed for main loop to work correctly
}

void EditExistingContact(vector <PersonalInformation> &ContactVect, const int &DisplaySpeed)//not cleaned up
{
    int ContactNumberToEdit;
    char FieldToEdit = 0;
    
    DisplayContacts(ContactVect, DisplaySpeed);
    
    cout << "Which contact would you like to edit: ";
    cin >> ContactNumberToEdit;
    cin.ignore();//remove newline left over from cin >> statement above
    
    ContactNumberToEdit--;//decrement value here to work with vector/array notation
    
    if (ContactNumberToEdit < ContactVect.size())//error will occur if tries to erase number outside of vector bound
    {
        cout << "\n\nContact you wish to edit: ";
        
        PrintVectorToScreen(ContactVect[ContactNumberToEdit].FirstNameVector);
        
        cout << "\nPress enter to skip editing a field.";
        cout << "\nPress \"Y\" + enter to edit a field.";
        
        cout << "\n\n======================\n\n";
        
        cout << "Original First Name:    ";
        PrintVectorToScreen(ContactVect[ContactNumberToEdit].FirstNameVector);
        
        cout << "Edit Field?: ";
        cin.get(FieldToEdit);//using cin.get() so that newlines are stored
        
        if (toupper(FieldToEdit) == 'Y')
        {
            cin.ignore();//clear left over newline in input buffer
            
            ContactVect[ContactNumberToEdit].FirstNameVector.clear();
            
            cout << "\nEnter New First Name:   ";
            InsertStringDataVectorFromKeyboard(ContactVect[ContactNumberToEdit].FirstNameVector);
            
            FieldToEdit = 0;//reset back to zero so next if condition isn't automatically met
        }
        
        cout << "\nOriginal Last Name:     ";
        PrintVectorToScreen(ContactVect[ContactNumberToEdit].LastNameVector);
        
        cout << "Edit Field?: ";
        cin.get(FieldToEdit);//using cin.get() so that newlines are stored
        
        if (toupper(FieldToEdit) == 'Y')
        {
            cin.ignore();//clear left over newline in input buffer
            
            ContactVect[ContactNumberToEdit].LastNameVector.clear();
            
            cout << "\nEnter New Last Name:    ";
            InsertStringDataVectorFromKeyboard(ContactVect[ContactNumberToEdit].LastNameVector);
            
            FieldToEdit = 0;//reset back to zero so next if condition isn't automatically met
        }
        
        cout << "\nOriginal Address:       ";
        PrintVectorToScreen(ContactVect[ContactNumberToEdit].AddressVector);
        
        cout << "Edit Field?: ";
        cin.get(FieldToEdit);//using cin.get() so that newlines are stored
        
        if (toupper(FieldToEdit) == 'Y')
        {
            cin.ignore();//clear left over newline in input buffer
            
            ContactVect[ContactNumberToEdit].AddressVector.clear();
            
            cout << "\nEnter New Address:      ";
            InsertStringDataVectorFromKeyboard(ContactVect[ContactNumberToEdit].AddressVector);
            
            FieldToEdit = 0;//reset back to zero so next if condition isn't automatically met
        }
        
        cout << "\nOriginal Phone Number:  ";
        PrintVectorToScreen(ContactVect[ContactNumberToEdit].PhoneNumberVector);
        
        cout << "Edit Field?: ";
        cin.get(FieldToEdit);//using cin.get() so that newlines are stored
        
        if (toupper(FieldToEdit) == 'Y')
        {
            cin.ignore();//clear left over newline in input buffer
            
            ContactVect[ContactNumberToEdit].PhoneNumberVector.clear();
            
            cout << "\nEnter New Phone Number: ";
            InsertStringDataVectorFromKeyboard(ContactVect[ContactNumberToEdit].PhoneNumberVector);
            
            FieldToEdit = 0;//reset back to zero so next if condition isn't automatically met
        }
        
        cout << "\nOriginal Date of Birth: ";
        PrintVectorToScreen(ContactVect[ContactNumberToEdit].DateOfBirth);
        
        cout << "Edit Field?: ";
        cin.get(FieldToEdit);//using cin.get() so that newlines are stored
        
        if (toupper(FieldToEdit) == 'Y')
        {
            cin.ignore();//clear left over newline in input buffer
            
            ContactVect[ContactNumberToEdit].DateOfBirth.clear();
            
            cout << "\nEnter New Date of Birth:";
            ContactVect[ContactNumberToEdit].CurrentAge = BirthDayInput(ContactVect[ContactNumberToEdit]);
            
            FieldToEdit = 0;//reset back to zero so next if condition isn't automatically met
        }
        
        cout << "\n\n======================\n\n";
    }
    
    SortContactVector(ContactVect);
}

void DeleteContact(vector <PersonalInformation> &ContactVect, const int &DisplaySpeed)//not cleaned up
{
    int ContactNumberToDelete;
    char ConfirmDelete = 0;
    char DeleteAnotherContactChoice;
    
    do
    {
        DisplayContacts(ContactVect, DisplaySpeed);//display list again
        
        cout << "Type in the number of the contact you wish to delete: ";
        cin >> ContactNumberToDelete;
        
        if (ContactNumberToDelete >= 0 && ContactNumberToDelete <= ContactVect.size())//error will occur if tries to erase number outside of vector bound
        {
            ContactNumberToDelete--;//decrement to work with vector/array notation
            
            cout << "\nYou are trying to delete: ";
            
            cout << "\n\n======================\n\n";
            
            cout << "First Name:    ";
            PrintVectorToScreen(ContactVect[ContactNumberToDelete].FirstNameVector);
            
            cout << "Last Name:     ";
            PrintVectorToScreen(ContactVect[ContactNumberToDelete].LastNameVector);
            
            cout << "Address:       ";
            PrintVectorToScreen(ContactVect[ContactNumberToDelete].AddressVector);
            
            cout << "Phone Number:  ";
            PrintVectorToScreen(ContactVect[ContactNumberToDelete].PhoneNumberVector);
            
            cout << "Date of Birth: ";
            PrintVectorToScreen(ContactVect[ContactNumberToDelete].DateOfBirth);
            
            cout << "Current Age:   ";
            cout << ContactVect[ContactNumberToDelete].CurrentAge;
            
            cout << "\n======================\n\n";
            
            
            cout << "\nAre you sure you want to delete ";
            
            for (int i = 0; ContactVect[ContactNumberToDelete].FirstNameVector[i] != '\n'; i++)//display name of contact being deleted
            {
                cout << ContactVect[ContactNumberToDelete].FirstNameVector[i];
            }
            
            cout << "? Y/N: ";
            cin >> ConfirmDelete;
            
            if (toupper(ConfirmDelete) == 'Y')
                ContactVect.erase(ContactVect.begin() + ContactNumberToDelete);
        }
        
        else
            cout << "\nNo contact located at this number";
        
        if (toupper(ConfirmDelete) == 'N' && ++ContactNumberToDelete <= ContactVect.size())//increment Contact to work properly with size()function
            cout << "\nNo contact deleted.";//if user chooses to not delete the contact
        
        cout << "\n\nDelete another contact? Y/N: ";
        cin >> DeleteAnotherContactChoice;
        cin.ignore();//removes 1 newline at the end of this function - needed for main loop to work correctly
    }
    while (toupper(DeleteAnotherContactChoice) == 'Y' && ContactVect.size() > 0);//don't try to delete when nothing is left in vector
    
    cout << "\n\n";
}

void DeleteAllContacts(vector <PersonalInformation> &ContactVect)//not cleaned up
{
    vector <char> UserChoice;
    bool ContactsNotDeletedFlag = true;
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
                ContactsNotDeletedFlag = false;
                ContactVect.clear();
                
                cout << "\nAll contacts have been deleted.\n\n";
            }
        }
    }
    
    if (ContactsNotDeletedFlag == true)
        cout << "\nContacts were not deleted.\n\n";
}

void DisplaySettingsMenu(const vector <PersonalInformation> &ContactVect, int &DisplaySpeed, int &SpeedSelectionChoice, bool &EncryptionMode)//not cleaned up
{
    int Choice;
    
    do
    {
        cout <<   "(1) Display Scroll Speed";
        cout << "\n(2) Encryption";
        cout << "\n(3) Quit Settings";
        
        cout << "\n\nChoice: ";
        cin >> Choice;
        
        switch (Choice)
        {
            case 1:
                ScrollSpeedSettingsAndUserInput(ContactVect, DisplaySpeed, SpeedSelectionChoice);
                break;
                
            case 2:
                EncryptionOnOffSetting(EncryptionMode);
                break;
                
            default:
                break;
        }
    }
    while (Choice >= 1 && Choice <= 2);
    
    cout << endl;
}

void EncryptionOnOffSetting(bool &EncryptionMode)//not cleaned up
{
    char UserChoice;
    
    cout << "\nEncyption ";
    
    if (EncryptionMode == true)
    {
        cout << "[on] / off";
        cout << "\n\nWould you like to turn encryption off? Y/N?: ";
        
        cin >> UserChoice;
        
        if (toupper(UserChoice) == 'Y')
            EncryptionMode = false;
    }
    
    else
    {
        cout << "on / [off]";
        cout << "\n\nWould you like to turn encryption on? Y/N?: ";
        
        cin >> UserChoice;
        
        if (toupper(UserChoice) == 'Y')
            EncryptionMode = true;
    }
    
    cout << endl;
}

void ScrollSpeedSettingsAndUserInput(const vector <PersonalInformation> &ContactVect, int &DisplaySpeed, int &SpeedSelectionChoice)//not cleaned up
{
    char LoopAgainOrNot = 'N';
    
    do
    {
        /* DISPLAY OPTIONS AND SHOW WHICH OPTION IS CURRENTLY SELECTED */
        
        cout << "Scrolling contact display rate: ";
        
        /* SLOW SPEED DISPLAY */
        
        cout << "\n\n(1)";
        
        if (SpeedSelectionChoice == 1)
            cout << " [*]";
        else
            cout << " [ ]";
        
        cout << " Slow";
        
        /* MEDIUM SPEED DISPLAY */
        
        cout << "\n(2)";
        
        if (SpeedSelectionChoice == 2)
            cout << " [*]";
        else
            cout << " [ ]";
        
        cout << " Medium";
        
        /* FAST SPEED DISPLAY */
        
        cout << "\n(3)";
        
        if (SpeedSelectionChoice == 3)
            cout << " [*]";
        else
            cout << " [ ]";
        
        cout << " Fast";
        
        
        cout << "\n(4)     Quit Settings";
        
        
        cout << "\n\n* = current option selected";
        
        cout << "\n\nSpeed Selection: ";
        
        cin >> SpeedSelectionChoice;
        
        ObtainSpeedSettingNumericalValues(DisplaySpeed, SpeedSelectionChoice);
        
        cout << "Preview of Speed:\n\n";
        
        DisplayContacts(ContactVect, DisplaySpeed);
        
        cout << "\nSet a different speeed? Y/N: ";
        cin >> LoopAgainOrNot;
        
        cout << "\n";
        cin.ignore();//remove one left over newline
    }
    while (toupper(LoopAgainOrNot) == 'Y');
}

void ObtainSpeedSettingNumericalValues(int &DisplaySpeed, const int &SpeedSelectionChoice)//not cleaned up
{
    /* VARIABLES THAT HOLD THE VARIOUS SPEEDS, EASY TO MODIFY THESE HERE */
    
    int Slow   = 140000;
    int Medium = 70000;
    int Fast   = 20000;
    
    /* INPUT CHOICE OF SPEED AND STORE SPEED IN DISPLAYSPEED */
    
    if (SpeedSelectionChoice == 1)
        DisplaySpeed = Slow;
    
    else if (SpeedSelectionChoice == 2)
        DisplaySpeed = Medium;
    
    else
        DisplaySpeed = Fast;
    
    //settings for displaying birthday reminders or not
}

void PrintVectorToFile(const vector <char> &ContactVect, ofstream &FileOut, const bool &EncryptionMode)//not cleaned up
{
    for (int i = 0; i < ContactVect.size(); i++)
    {
        FileOut << EncryptDecryptChar(ContactVect[i], EncryptionMode);
    }
}

void PrintVectorToScreen(const vector <char> &ContactVect)//not cleaned up
{
    for (int i = 0; i < ContactVect.size(); i++)
    {
        cout << ContactVect[i];
    }
}

void InsertStringInVectorFromFile(vector <char> &ContactVect, ifstream &FileIn, const bool &EncryptionMode)//not cleaned up
{
    char Insert = 1;//used for inserting characters into individual struct vectors
                    //initialized at 1 to allow while loop to execute
    
    while (Insert != '\n')
    {
        FileIn.get(Insert);
        
        Insert = EncryptDecryptChar(Insert, EncryptionMode);
        
        ContactVect.push_back(Insert);
    }
}

void InsertStringDataVectorFromKeyboard(vector <char> &ContactVect)//not cleaned up
{
    char Insert = 0;//used for inserting characters into individual struct vectors
    //initialized at 0 to allow while loop to execute
    
    char NameOfEmptyField[] = {"N/A\n"};
    
    while (Insert != '\n')
    {
        cin.get(Insert);//using cin.get, and not cin >>, so it stores the newline in Insert - allows to break out of loop
        
        ContactVect.push_back(Insert);
    }
    
    if (ContactVect.size() <= 1)//if theres nothing in vector or just a newline, add "N/A" text in field
    {
        ContactVect.erase(ContactVect.begin());//erase newline stored
        
        for (int i = 0; NameOfEmptyField[i] != 0; i++)
        {
            ContactVect.push_back(NameOfEmptyField[i]);//insert text for "N/A"
        }
    }
    
    while (ContactVect[0] == ' ')//remove any leading whitespace from vector
        ContactVect.erase(ContactVect.begin());//while first element is a space, delete first element
    
    if (!isnumber(ContactVect[0]))
        (ContactVect[0] = toupper(ContactVect[0]));//if not a number, always capitalize (for first name and last names)
}

void SortContactVector(vector <PersonalInformation> &ContactVect)//my modified bubble sort code I found online//not cleaned up
{
    bool SwapsMade = true;
    
    while(SwapsMade)
    {
        SwapsMade = false;
        
        for (int i = 0; i < ContactVect.size()-1; i++)
        {
            if (!NamesInOrder(ContactVect[i].LastNameVector, ContactVect[i+1].LastNameVector, ContactVect[i].FirstNameVector, ContactVect[i+1].FirstNameVector))
            {
                swap(ContactVect[i], ContactVect[i+1]);
                
                SwapsMade = true;
            }
        }
    }
}

bool NamesInOrder(const vector <char> &LastNameVect1, const vector <char> &LastNameVect2, const vector <char> &FirstNameVect1, const vector <char> &FirstNameVect2)//not cleaned up
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

void RebuildContactBook(vector <PersonalInformation> &ContactVect, const char Path[], int &SpeedSelectionChoice, bool &EncryptionMode)//not cleaned up
{
    PersonalInformation Temporary;
    int AmountOfContactsInFile;
    
    ifstream FileIn;
    
    FileIn.open(Path);
    
    /* CHECK TO SEE IF FILE OPENS */
    
    if (FileIn.fail())
    {
        cout << "Couldn't Open File\n";
        return;
    }
    
    FileIn.ignore(15);//ignore "Security Mode: " text
    
    FileIn >> EncryptionMode;
    
    FileIn.ignore(24);//ignore "Speed Selection Choice: " text
    
    FileIn >> SpeedSelectionChoice;
    
    FileIn.ignore();// ignore single newline between numbers
    
    FileIn.ignore(20);// ignore "Number of Contacts: " text
    
    AmountOfContactsInFile = FileIn.get() - 48;// convert from char to number
    
    FileIn.ignore(2);// ignore two newlines after
    
    for (int i = 0; ContactVect.size() < AmountOfContactsInFile; i++)
    {
        /* DECRYPTION FOR VECTORS HAPPENS IN INSERTSTRINGIN... FUNCTIONS */
        
        InsertStringInVectorFromFile(Temporary.FirstNameVector, FileIn, EncryptionMode);
        
        InsertStringInVectorFromFile(Temporary.LastNameVector, FileIn, EncryptionMode);
        
        InsertStringInVectorFromFile(Temporary.AddressVector, FileIn, EncryptionMode);
        
        InsertStringInVectorFromFile(Temporary.PhoneNumberVector, FileIn, EncryptionMode);
        
        InsertStringInVectorFromFile(Temporary.DateOfBirth, FileIn, EncryptionMode);
        
        /* DECRYPTION FOR INTS HAPPENS RIGHT HERE */
        
        FileIn >> Temporary.CurrentAge;
        Temporary.CurrentAge = EncryptDecryptInt(Temporary.CurrentAge, EncryptionMode);
        
        FileIn >> Temporary.MonthBorn;
        Temporary.MonthBorn = EncryptDecryptInt(Temporary.MonthBorn, EncryptionMode);
        
        FileIn >> Temporary.DayBorn;
        Temporary.DayBorn = EncryptDecryptInt(Temporary.DayBorn, EncryptionMode);
        
        FileIn >> Temporary.YearBorn;
        Temporary.YearBorn = EncryptDecryptInt(Temporary.YearBorn, EncryptionMode);
        
        /* AUTOMATICALLY RECALCULATE CURRENT YEAR EVERY TIME LIST IS REBUILT */
        
        Temporary.CurrentAge = CalculateCurrentAge(Temporary, Temporary.MonthBorn, Temporary.DayBorn, Temporary.YearBorn);
    
        ContactVect.push_back(Temporary);
        
        ClearDataVectorsFromStructure(Temporary);
        
        FileIn.ignore(2);//ignore two newlines between contacts (two newlines because last item is an int and doesn't store the newline like the vectors do)
    }
    
    /* SAVED CONTACTS AFTER READING IN CASE AGES WERE UPDATED AFTER RE-CALCULATING CURRENT AGE */
    
    SaveContactBookAndSettings(ContactVect, Path, SpeedSelectionChoice, EncryptionMode);
    
    FileIn.close();
}

void CreateFolderAndTextFile(char FullPath[])//not cleaned up
{
    //optaining pathway on mac / making my custom folder - consider another implementation that uses vector?
    
    const char *HomeAndUserNamePath = getenv("HOME");//get home/username path - finds username
    const char *MorePath = "/Library/Application Support/The Lyons' Den Labs";
    const char *RestOfPath = "/TheLyons'DenContactInformation2.txt";
    
    strcat(FullPath, HomeAndUserNamePath);
    strcat(FullPath, MorePath);
    
    mkdir(FullPath, ACCESSPERMS);//make The Lyons' Den Labs folder
    
    strcat(FullPath, RestOfPath);
}

bool CheckIfFileExistsAndContainsInformation(const char Path[])//shouldn't be declaring a new variable, should be passing it in, but that would call for a major rewrite of the menu function and all the function parameters//not cleaned up
{
    ifstream FileIn;
    
    FileIn.open(Path);
    
    /* CHECK TO MAKE SURE FILE OPENED */
    
    if (FileIn.fail())
    {
        FileIn.close();
        return false;
    }
    
    /* CHECK TO SEE IF FILE IS EMPTY */
    
    else if (FileIn.eof())
    {
        FileIn.close();
        return false;
    }
    
    /* ONLY RETURN TRUE IF BOTH PREVIOUS CONDITIONS ARE NOT MET */
    
    else
    {
        FileIn.close();
        return true;
    }
}

void ClearDataVectorsFromStructure(PersonalInformation &TemporaryStorage)//not cleaned up
{
    /* GET BACK THE MEMORY THAT WAS ASSIGNED TO THESE VECTORS */
    /* USING SWAP METHOD ON VECTORS AS DESCRIBED IN MY STACK EXCHANGE QUESTION BELOW */
    /* http://stackoverflow.com/questions/39090554/questions-about-vectors-and-deleting-memory-associated-with-them?noredirect=1#comment65529507_39090554 */
    
    vector<char>().swap(TemporaryStorage.FirstNameVector);
    vector<char>().swap(TemporaryStorage.LastNameVector);
    vector<char>().swap(TemporaryStorage.AddressVector);
    vector<char>().swap(TemporaryStorage.PhoneNumberVector);
    vector<char>().swap(TemporaryStorage.DateOfBirth);
    
    /* DESTROY ALL CHARACTERS FROM EACH VECTOR OF TEMP STORAGE TO GET READY FOR NEXT */
    
    TemporaryStorage.FirstNameVector.clear();
    TemporaryStorage.LastNameVector.clear();
    TemporaryStorage.AddressVector.clear();
    TemporaryStorage.PhoneNumberVector.clear();
    TemporaryStorage.DateOfBirth.clear();
}

int BirthDayInput(PersonalInformation &TempPersonalInfoHolder)//not cleaned up
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

int CalculateCurrentAge(PersonalInformation &TempPersonalInfoHolder, const int &MonthBorn, const int &DayBorn, const int &YearBorn)//not cleaned up
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
    
    /* CALCULATE HOW CLOSE CONTACT'S BIRTHDAY IS */
    
    TempPersonalInfoHolder.BirthdayIsInXDays = DayOfTheYearBirthdayLandsOn - CurrentDayOfThisYear;
    
    return UsersCurrentAge;
}

int CalculateDayNumberFromMonthAndDay(const int &BirthMonth, const int &BirthDay, const int &CurrentYear)//not cleaned up
{
    int DayOfYearThatBirthdayIsOn = 0;
    int TemporaryDayHolder = 0;
    
    if (BirthMonth >= 1)//January - 31
    {
        DayOfYearThatBirthdayIsOn += TemporaryDayHolder;
        TemporaryDayHolder = 31;
    }
    
    if (BirthMonth >= 2)//February - 28/29
    {
        DayOfYearThatBirthdayIsOn += TemporaryDayHolder;
        TemporaryDayHolder = 28;
        
        /* CHECK TO SEE IF LEAP YEAR OR NOT */
        
        if (CurrentYear % 4 == 0)
        {
            if (CurrentYear % 100 == 0)
            {
                if (CurrentYear % 400 == 0)
                    TemporaryDayHolder = 29;
            }
            
            else
                TemporaryDayHolder = 29;
            
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
        DayOfYearThatBirthdayIsOn += TemporaryDayHolder;
        TemporaryDayHolder = 31;
    }
    
    if (BirthMonth >= 4)//April - 30
    {
        DayOfYearThatBirthdayIsOn += TemporaryDayHolder;
        TemporaryDayHolder = 30;
    }
    
    if (BirthMonth >= 5)//May - 31
    {
        DayOfYearThatBirthdayIsOn += TemporaryDayHolder;
        TemporaryDayHolder = 31;
    }
    
    if (BirthMonth >= 6)//June - 30
    {
        DayOfYearThatBirthdayIsOn += TemporaryDayHolder;
        TemporaryDayHolder = 30;
    }
    
    if (BirthMonth >= 7)//July - 31
    {
        DayOfYearThatBirthdayIsOn += TemporaryDayHolder;
        TemporaryDayHolder = 31;
    }
    
    if (BirthMonth >= 8)//August - 31
    {
        DayOfYearThatBirthdayIsOn += TemporaryDayHolder;
        TemporaryDayHolder = 31;
    }
    
    if (BirthMonth >= 9)//September - 30
    {
        DayOfYearThatBirthdayIsOn += TemporaryDayHolder;
        TemporaryDayHolder = 30;
    }
    
    if (BirthMonth >= 10)//October - 31
    {
        DayOfYearThatBirthdayIsOn += TemporaryDayHolder;
        TemporaryDayHolder = 31;
    }
    
    if (BirthMonth >= 11)//November - 30
    {
        DayOfYearThatBirthdayIsOn += TemporaryDayHolder;
        TemporaryDayHolder = 30;
    }
    
    if (BirthMonth >= 12)//December - 31
    {
        DayOfYearThatBirthdayIsOn += TemporaryDayHolder;
        TemporaryDayHolder = 31;
    }
    
    DayOfYearThatBirthdayIsOn += BirthDay;
    
    return DayOfYearThatBirthdayIsOn;
}

void StoreDateOfBirthInVector(PersonalInformation &TempPersonalInfoHolder)//not cleaned up
{
    const char *MonthNames[12] = {"January",   "February", "March",    "April",
                                  "May",       "June",     "July",     "August",
                                  "September", "October",  "November", "December"};
    
    /* PLACING DATA MEMBERS INTO TEMPORARY VARIABLES BECAUSE THE VALUES OF THE VARIABLES WILL BE CHANGED */
    /* DONT WANT TO CHANGE THE DATA MEMBERS THOUGH */
    
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
                TempPersonalInfoHolder.DateOfBirth.push_back('\n');
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
        DayArray[i] = (TempDay % 10) + 48;//convertion to char happens here
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
    
    TempPersonalInfoHolder.DateOfBirth.push_back('\n');}

char EncryptDecryptChar(char Input, const bool &EncryptionMode)//not cleaned up
{
    /* USED TO ENCRYPT/DECRYPT THE VECTORS IN STRUCT: FIRSTNAME, LASTNAME, ADDRESS, PHONENUMBER,DATEOFBIRTH */
    /* FIRST USE A SIMPLE, HARDCODED VALUE FOR ENCRYPTION, THEN MAKE IT MORE COMPLEX */
    
    char CharKey = 'J';
    
    /* ONLY ENCRYPT TEXT IF ENCRYPT MODE IS TRUE (TURNED ON), ELSE, SKIP IT AND PRINT NORMAL */
    
    if (EncryptionMode == true)
    {
        Input ^= CharKey;
    }
    
    return Input;
}

int EncryptDecryptInt(int Input, const bool &EncryptionMode)//not cleaned up
{
    /* USED TO ENCRYPT/DECRYPT INTS IN STRUCT: MONTHBORN, DAYBORN, YEARBORN AND CURRENTAGE */
    /* FIRST USE A SIMPLE, HARDCODED VALUE FOR ENCRYPTION, THEN MAKE IT MORE COMPLEX */
    /* USE A DIFFERENT METHOD OF ENCRYPTION FOR THE INTS */
    
    char IntKey = 'z';
    
    /* ONLY ENCRYPT TEXT IF ENCRYPT MODE IS TRUE (TURNED ON), ELSE, SKIP IT AND PRINT NORMAL */
    
    if (EncryptionMode == true)
    {
        Input ^= IntKey;
    }
    
    return Input;
}

void SaveContactBookAndSettings(const vector <PersonalInformation> &ContactVect, const char Path[], const int &SpeedSelectionChoice, const bool &EncryptionMode)//not cleaned up
{
    ofstream FileOut;
    
    
    FileOut.open(Path);
    
    if (FileOut.fail())//check to see if file opened
        cout << "Couldn't Open File\n";
    
    
    FileOut << "Security Mode: ";
    
    FileOut << EncryptionMode << endl;
    
    FileOut << "Speed Selection Choice: ";
    
    FileOut << SpeedSelectionChoice << endl;
    
    /* SAVE NUMBER OF CONTACTS TO .TXT FILE SO WE KNOW HOW MANY WE ARE READING IN IN THE REBUILD FUNCTION */
    
    FileOut << "Number of Contacts: ";
    
    FileOut << ContactVect.size() << endl << endl;
    
    for (int i = 0; i < ContactVect.size(); i++)
    {
        /* ENCRYPTION FOR VECTORS HAPPENS IN PRINTSTRINGSTRUCT... FUNCTIONS */
        
        PrintVectorToFile(ContactVect[i].FirstNameVector, FileOut, EncryptionMode);
        
        PrintVectorToFile(ContactVect[i].LastNameVector, FileOut, EncryptionMode);
        
        PrintVectorToFile(ContactVect[i].AddressVector, FileOut, EncryptionMode);
        
        PrintVectorToFile(ContactVect[i].PhoneNumberVector, FileOut, EncryptionMode);
        
        PrintVectorToFile(ContactVect[i].DateOfBirth, FileOut, EncryptionMode);
        
        /* ENCRYPTION FOR INTS HAPPENS RIGHT HERE */
        
        FileOut << EncryptDecryptInt(ContactVect[i].CurrentAge, EncryptionMode) << endl;
        
        FileOut << EncryptDecryptInt(ContactVect[i].MonthBorn, EncryptionMode) << endl;
        
        FileOut << EncryptDecryptInt(ContactVect[i].DayBorn, EncryptionMode) << endl;
        
        FileOut << EncryptDecryptInt(ContactVect[i].YearBorn, EncryptionMode);
        
        FileOut << "\n\n";
    }
    
    FileOut << "Contacts Last Altered: " << ObtainDateAndTime() << endl;
    
    FileOut.close();
}

string ObtainDateAndTime()//not my code here - modified it to display what I want and to read easier
{
    char Time[50];
    
    time_t now = time(NULL);
    
    strftime(Time, 50, "%D, %I:%M %p", localtime(&now));
    
    return string(Time);
}