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

void MainMenu();

/* MAIN MENU FUNCTIONS */

void DisplayContacts(const vector <PersonalInformation> &CV, const int & DisplaySpeed);
void AddContact(vector <PersonalInformation> &CV, const char Path[], int & SpeedSelectionChoice);
void EditExistingContact(vector <PersonalInformation> &Vector, const char Path[], const int & DisplaySpeed, int & SpeedSelectionChoice);
void DeleteContact(vector <PersonalInformation> &CV, const char Path[], const int & DisplaySpeed, int & SpeedSelectionChoice);
void DeleteAllContacts(vector <PersonalInformation> &Vector, const char Path[], int & SpeedSelectionChoice);
void DisplaySettingsMenu(int & DisplaySpeed, int & SpeedSelectionChoice, vector <PersonalInformation> CV, bool & EncryptionMode);

void EncryptionOnOff(bool & EncryptionMode);
void SpeedSettingsAndUserInput(int & DisplaySpeed, int & SpeedSelectionChoice, vector <PersonalInformation> CV);
void ObtainSpeedSettingNumericalValues(int & DisplaySpeed, int & SpeedSelectionChoice);

/* FUNCTIONS FROM READING AND WRITING FROM FILES AND FROM KEYBOARD */

void PrintStringInStructDataVectorToFile(const vector <char> &Vector, ofstream &FileOut);
void PrintStringInStructDataVectorToScreen(const vector <char> &Vector);
void InsertStringInStructDataVectorFromFile(vector <char> &Vector, ifstream &FileIn);
void InsertStringInStructDataVectorFromKeyboard(vector <char> &Vector);

/* SORTING FUNCTIONS */

void SortVector(vector <PersonalInformation> &CV);
bool NamesInOrder(vector <char> LastNameVect1, vector <char> LastNameVect2, vector <char> FirstNameVect1, vector <char>
                  FirstNameVect2);

/* MISCELLANEOUS FUNCTIONS */

void RebuildContactBook(vector <PersonalInformation> &CV, const char Path[], int & SpeedSelectionChoice);
void CreateFolderAndTextFile(char FullPath[]);
bool EmptyFileChecker(const char Path[]);
void ClearDataVectorsFromStructure(PersonalInformation &X);

/* FUNCTIONS FOR DYNAMIC AGE/BIRTHDAY */
 
int BirthDayInput(PersonalInformation & TempPersonalInfoHolder);
int CalculateCurrentAge(PersonalInformation & TempPersonalInfoHolder, int & MonthBorn, int & DayBorn, int & YearBorn);
int CalculateDayNumberFromMonthAndDay(const int & BirthMonth, const int & BirthDay, const int & CurrentYear);
void StoreDateOfBirthInVector(PersonalInformation & PersonalInformationVector);

/* FUNCTIONS FOR ENCRYPTION/DECRYPTION */

char EncryptDecryptChar(char Input);
int EncryptDecryptInt(int Input);

/* FUNCTIONS FOR SAVING */

void SaveContactBookAndSettings(vector <PersonalInformation> &CV, const char Path[], int & SpeedSelectionChoice);
string Date();

/*
 -----------------------------BUGS AND FIXES------------------------------
 fix error in calculating encrypted
 
 organize function prototypes again
 
 how big to make array holding pathway? - any way to use vector for this field?

 support to just type in newlines to skip birthday, instead of using 0 - use of cin.get() and chars, not int
 --use temp char variables in birthday input, then convert them to numbers, so I dont have to change the data
 --members from int to char, which would be a lot of extra work
 
 bound checking on birthday entry
 -no months greater than 12
 -no days greater than 31
 
 use constant reference for parameters when possible to not only keep values from being changed
 but to use less memory
 
 work on optimizing code by changing int to short int or using characters - in functions and in struct
 
 bring the boundchecking (no contact at this location) over from deleting function to edit function
 
 change birthday reminder from struct data member to variable in display function that holds number
 and displays to screen, being overwrtten each time - maybe
 
 ---------------------------NEW FEATURES TO ADD---------------------------
 password protect the encryption by using a password and cycling the letters of the password
    then going back to the beginning of that password and doing it again until its done
 
 in settings section, ask if user wants encryption or not, if yes, turn it on, if not, turn it off
 
 expand more in the user settings
 
 ways to exit main menu functions - type "Q" to leave - then if statement with "return/break"
 enhance loop in delete contact function?
 -support to type in multiple numbers, separated by spaces, to delete a bunch at once
 support to let user know when a person's birthday is, up to 7 days before it comes, and
    exactly how many days it is until their birthday
 
 search for contact function
 
*/

int main()
{
    MainMenu();//consider removing this function entirely and just placing all inside main()
}

void MainMenu()
{
    vector <PersonalInformation> ContactVector;
    static int MainMenuPauseCounter = 0;
    
    char FullPath[180] = {0};
    
    int SwitchChoice;
    int DisplaySpeed = 60000;//defaults at 60,000 - which is medium speed in the SettingsAndConfiguration() function
    int SpeedSelectionChoice = 2;//defaults at medium speed
    bool EncryptionMode;
    
    
    CreateFolderAndTextFile(FullPath);//creates The Lyons' Den Labs folder in Application Support folder in Library
    
    if(EmptyFileChecker(FullPath))
    {
        RebuildContactBook(ContactVector, FullPath, SpeedSelectionChoice);//restort contacts
        ObtainSpeedSettingNumericalValues(DisplaySpeed, SpeedSelectionChoice);//restore user settings
    }
    
    do
    {
        if (MainMenuPauseCounter++ > 0)//skip this set of commands for the first time in the menu, enter every time after
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
        cin.ignore();
        
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
                AddContact(ContactVector, FullPath, SpeedSelectionChoice);
                SaveContactBookAndSettings(ContactVector, FullPath, SpeedSelectionChoice);
                break;
            }
                
            case 3:
            {
                EditExistingContact(ContactVector, FullPath, DisplaySpeed, SpeedSelectionChoice);
                SaveContactBookAndSettings(ContactVector, FullPath, SpeedSelectionChoice);
                break;
            }
                
            case 4:
            {
                DeleteContact(ContactVector, FullPath, DisplaySpeed, SpeedSelectionChoice);
                SaveContactBookAndSettings(ContactVector, FullPath, SpeedSelectionChoice);
                break;
            }
                
            case 5:
            {
                DeleteAllContacts(ContactVector, FullPath, SpeedSelectionChoice);
                SaveContactBookAndSettings(ContactVector, FullPath, SpeedSelectionChoice);
                break;
            }
                
            case 6:
            {
                DisplaySettingsMenu(DisplaySpeed, SpeedSelectionChoice, ContactVector, EncryptionMode);
                SaveContactBookAndSettings(ContactVector, FullPath, SpeedSelectionChoice);
                break;
            }
                
            default:
                break;
        }
    }
    while (SwitchChoice != 7);
}

void DisplayContacts(const vector<PersonalInformation> &CV, const int & DisplaySpeed)
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
        
        cout << "Date Of Birth:  ";
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
        
        /* IF BIRTHDAY IS LESS THAN 7 DAYS AWAY, DISPLAY THAT INFORMATION TO THE SCREEEN */
        
        if (CV[i].BirthdayIsInXDays >= 0 && CV[i].BirthdayIsInXDays <= 7)
            cout << "\n*BIRTHDAY IS IN " << CV[i].BirthdayIsInXDays << " DAYS*";
        
        cout << "\n\n";
        
        usleep(DisplaySpeed);
    }
    
    if (CV.size() == 0)
        cout << "Contact Book is empty.\n\n";
    
    cout << "======================\n\n";
}

void AddContact(vector <PersonalInformation> &CV, const char Path[], int & SpeedSelectionChoice)
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
        
        cout << "\nAdd another contact? Y/N: ";
        cin >> UserChoice;
        
        if (toupper(UserChoice) == 'Y')//dont cin.ignore() if user doesn't repeat loop, used to keep main from pausing too many times
            cin.ignore();//clear newline from cin >> statement above
        
        cout << "\n";
    }
    
    cin.ignore();//removes 1 newline at the end of this function - needed for main loop to work correctly
}

void EditExistingContact(vector <PersonalInformation> &Vector, const char Path[], const int & DisplaySpeed, int & SpeedSelectionChoice)
{
    int ContactNumberToEdit;
    char FieldToEdit = 0;
    
    DisplayContacts(Vector, DisplaySpeed);
    
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
        
        cout << "Original First Name:    ";
        PrintStringInStructDataVectorToScreen(Vector[ContactNumberToEdit].FirstNameVector);
        
        cout << "Edit Field?: ";
        cin.get(FieldToEdit);//using cin.get() so that newlines are stored
        
        if (toupper(FieldToEdit) == 'Y')
        {
            cin.ignore();//clear left over newline in input buffer
            
            Vector[ContactNumberToEdit].FirstNameVector.clear();
            
            cout << "\nEnter New First Name:   ";
            InsertStringInStructDataVectorFromKeyboard(Vector[ContactNumberToEdit].FirstNameVector);
            
            FieldToEdit = 0;//reset back to zero so next if condition isn't automatically met
        }
        
        cout << "\nOriginal Last Name:     ";
        PrintStringInStructDataVectorToScreen(Vector[ContactNumberToEdit].LastNameVector);
        
        cout << "Edit Field?: ";
        cin.get(FieldToEdit);//using cin.get() so that newlines are stored
        
        if (toupper(FieldToEdit) == 'Y')
        {
            cin.ignore();//clear left over newline in input buffer
            
            Vector[ContactNumberToEdit].LastNameVector.clear();
            
            cout << "\nEnter New Last Name:    ";
            InsertStringInStructDataVectorFromKeyboard(Vector[ContactNumberToEdit].LastNameVector);
            
            FieldToEdit = 0;//reset back to zero so next if condition isn't automatically met
        }
        
        cout << "\nOriginal Address:       ";
        PrintStringInStructDataVectorToScreen(Vector[ContactNumberToEdit].AddressVector);
        
        cout << "Edit Field?: ";
        cin.get(FieldToEdit);//using cin.get() so that newlines are stored
        
        if (toupper(FieldToEdit) == 'Y')
        {
            cin.ignore();//clear left over newline in input buffer
            
            Vector[ContactNumberToEdit].AddressVector.clear();
            
            cout << "\nEnter New Address:      ";
            InsertStringInStructDataVectorFromKeyboard(Vector[ContactNumberToEdit].AddressVector);
            
            FieldToEdit = 0;//reset back to zero so next if condition isn't automatically met
        }
        
        cout << "\nOriginal Phone Number:  ";
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
        
        cout << "\nOriginal Date of Birth: ";
        PrintStringInStructDataVectorToScreen(Vector[ContactNumberToEdit].DateOfBirth);
        
        cout << "Edit Field?: ";
        cin.get(FieldToEdit);//using cin.get() so that newlines are stored
        
        if (toupper(FieldToEdit) == 'Y')
        {
            cin.ignore();//clear left over newline in input buffer
            
            Vector[ContactNumberToEdit].DateOfBirth.clear();
            
            cout << "\nEnter New Date of Birth:";
            Vector[ContactNumberToEdit].CurrentAge = BirthDayInput(Vector[ContactNumberToEdit]);
            
            FieldToEdit = 0;//reset back to zero so next if condition isn't automatically met
        }
        
        cout << "\n\n======================\n\n";
    }
    
    SortVector(Vector);
}

void DeleteContact(vector <PersonalInformation> &CV, const char Path[], const int & DisplaySpeed, int & SpeedSelectionChoice)
{
    int ContactNumberToDelete;
    char ConfirmDelete = 0;
    char DeleteAnotherContactChoice;
    
    do
    {
        DisplayContacts(CV, DisplaySpeed);//display list again
        
        cout << "Type in the number of the contact you wish to delete: ";
        cin >> ContactNumberToDelete;
        
        if (ContactNumberToDelete >= 0 && ContactNumberToDelete <= CV.size())//error will occur if tries to erase number outside of vector bound
        {
            ContactNumberToDelete--;//decrement to work with vector/array notation
            
            cout << "\nYou are trying to delete: ";
            
            cout << "\n\n======================\n\n";
            
            cout << "First Name:    ";
            PrintStringInStructDataVectorToScreen(CV[ContactNumberToDelete].FirstNameVector);
            
            cout << "Last Name:     ";
            PrintStringInStructDataVectorToScreen(CV[ContactNumberToDelete].LastNameVector);
            
            cout << "Address:       ";
            PrintStringInStructDataVectorToScreen(CV[ContactNumberToDelete].AddressVector);
            
            cout << "Phone Number:  ";
            PrintStringInStructDataVectorToScreen(CV[ContactNumberToDelete].PhoneNumberVector);
            
            cout << "Date of Birth: ";
            PrintStringInStructDataVectorToScreen(CV[ContactNumberToDelete].DateOfBirth);
            
            cout << "Current Age:   ";
            cout << CV[ContactNumberToDelete].CurrentAge;
            
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
        
        cout << "\n\nDelete another contact? Y/N: ";
        cin >> DeleteAnotherContactChoice;
        cin.ignore();//removes 1 newline at the end of this function - needed for main loop to work correctly
    }
    while (toupper(DeleteAnotherContactChoice) == 'Y' && CV.size() > 0);//don't try to delete when nothing is left in vector
    
    cout << "\n\n";
}

void DeleteAllContacts(vector <PersonalInformation> &Vector, const char Path[], int & SpeedSelectionChoice)
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
                Vector.clear();
                
                cout << "\nAll contacts have been deleted.\n\n";
            }
        }
    }
    
    if (ContactsNotDeletedFlag == true)
        cout << "\nContacts were not deleted.\n\n";
}

void DisplaySettingsMenu(int & DisplaySpeed, int & SpeedSelectionChoice, vector <PersonalInformation> CV, bool & EncryptionMode)
{
    int Choice;
    
    do
    {
        cout <<   "(1) Display Speed";
        cout << "\n(2) Encryption Settings";
        cout << "\n(3) QUIT SETTINGS";
        
        cout << "\n\nChoice: ";
        cin >> Choice;
        
        switch (Choice)
        {
            case 1:
                SpeedSettingsAndUserInput(DisplaySpeed, SpeedSelectionChoice, CV);
                break;
                
            case 2:
                EncryptionOnOff(EncryptionMode);
                break;
                
            default:
                break;
        }
    }
    while (Choice >= 1 && Choice <= 2);
}

void EncryptionOnOff(bool & EncryptionMode)
{
    char UserChoice;
    
    cout << "Encyption ";
    
    if (EncryptionMode == true)
    {
        cout << "[on] / off";
        cout << "\n\nWould you like to turn encryptoin off? Y/N?: ";
        
        cin >> UserChoice;
        
        if (toupper(UserChoice) == 'Y')
            EncryptionMode = false;
    }
    
    else
    {
        cout << "on / [off]";
        cout << "\n\nWould you like to turn encryptoin on? Y/N?: ";
        
        cin >> UserChoice;
        
        if (toupper(UserChoice) == 'Y')
            EncryptionMode = true;
    }
}

//RENAME BOTH FUNCTIONS BELOW TO SOMETHING THAT FITS JUST FOR SPEED SETTINGS
void SpeedSettingsAndUserInput(int & DisplaySpeed, int & SpeedSelectionChoice, vector <PersonalInformation> CV)
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
        
        DisplayContacts(CV, DisplaySpeed);
        
        cout << "\nSet a different speeed? Y/N: ";
        cin >> LoopAgainOrNot;
        
        cout << "\n";
        cin.ignore();//remove one left over newline
    }
    while (toupper(LoopAgainOrNot) == 'Y');
}

void ObtainSpeedSettingNumericalValues(int & DisplaySpeed, int & SpeedSelectionChoice)
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

void PrintStringInStructDataVectorToFile(const vector <char> &Vector, ofstream &FileOut)
{
    for (int i = 0; i < Vector.size(); i++)
    {
        FileOut << EncryptDecryptChar(Vector[i]);
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
    
    while (Insert != '\n')
    {
        FileIn.get(Insert);
        
        Insert = EncryptDecryptChar(Insert);
        
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

void RebuildContactBook(vector <PersonalInformation> &CV, const char Path[], int & SpeedSelectionChoice)
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
    
    FileIn.ignore(24);//ignore "Speed Selection Choice: " text
    
    FileIn >> SpeedSelectionChoice;
    
    FileIn.ignore();// ignore single newline between numbers
    
    FileIn.ignore(20);// ignore "Number of Contacts: " text
    
    AmountOfContactsInFile = FileIn.get() - 48;// convert from char to number
    
    FileIn.ignore(2);// ignore two newlines after
    
    for (int i = 0; CV.size() < AmountOfContactsInFile; i++)
    {
        /* DECRYPTION FOR VECTORS HAPPENS IN INSERTSTRINGIN... FUNCTIONS */
        
        InsertStringInStructDataVectorFromFile(Temporary.FirstNameVector, FileIn);
        
        InsertStringInStructDataVectorFromFile(Temporary.LastNameVector, FileIn);
        
        InsertStringInStructDataVectorFromFile(Temporary.AddressVector, FileIn);
        
        InsertStringInStructDataVectorFromFile(Temporary.PhoneNumberVector, FileIn);
        
        InsertStringInStructDataVectorFromFile(Temporary.DateOfBirth, FileIn);
        
        /* DECRYPTION FOR INTS HAPPENS RIGHT HERE */
        
        FileIn >> Temporary.CurrentAge;
        Temporary.CurrentAge = EncryptDecryptInt(Temporary.CurrentAge);
        
        FileIn >> Temporary.MonthBorn;
        Temporary.MonthBorn = EncryptDecryptInt(Temporary.MonthBorn);
        
        FileIn >> Temporary.DayBorn;
        Temporary.DayBorn = EncryptDecryptInt(Temporary.DayBorn);
        
        FileIn >> Temporary.YearBorn;
        Temporary.YearBorn = EncryptDecryptInt(Temporary.YearBorn);
        
        /* AUTOMATICALLY RECALCULATE CURRENT YEAR EVERY TIME LIST IS REBUILT */
        
        Temporary.CurrentAge = CalculateCurrentAge(Temporary, Temporary.MonthBorn, Temporary.DayBorn, Temporary.YearBorn);
    
        CV.push_back(Temporary);
        
        ClearDataVectorsFromStructure(Temporary);
        
        FileIn.ignore(2);//ignore two newlines between contacts (two newlines because last item is an int and doesn't store the newline like the vectors do)
    }
    
    /* SAVED CONTACTS AFTER READING IN CASE AGES WERE UPDATED AFTER RE-CALCULATING CURRENT AGE */
    
    SaveContactBookAndSettings(CV, Path, SpeedSelectionChoice);
    
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

void ClearDataVectorsFromStructure(PersonalInformation &X)
{
    X.FirstNameVector.clear();//clear out all vectors of temporary storage to get ready for next
    X.LastNameVector.clear();
    X.AddressVector.clear();
    X.PhoneNumberVector.clear();
    X.DateOfBirth.clear();
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
    
    /* CALCULATE HOW CLOSE CONTACT'S BIRTHDAY IS */
    
    TempPersonalInfoHolder.BirthdayIsInXDays = DayOfTheYearBirthdayLandsOn - CurrentDayOfThisYear;
    
    return UsersCurrentAge;
}

int CalculateDayNumberFromMonthAndDay(const int & BirthMonth, const int & BirthDay, const int & CurrentYear)
{
    int DayOfYearThatBirthdayIsOn = 0;
    int DayHolder = 0;
    
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
    
    TempPersonalInfoHolder.DateOfBirth.push_back('\n');
}

char EncryptDecryptChar(char Input)
{
    /* USED TO ENCRYPT/DECRYPT THE VECTORS IN STRUCT: FIRSTNAME, LASTNAME, ADDRESS, PHONENUMBER,DATEOFBIRTH */
    /* FIRST USE A SIMPLE, HARDCODED VALUE FOR ENCRYPTION, THEN MAKE IT MORE COMPLEX */
    
    char CharKey = 'J';
    
    Input ^= CharKey;
    
    return Input;
}

int EncryptDecryptInt(int Input)
{
    /* USED TO ENCRYPT/DECRYPT INTS IN STRUCT: MONTHBORN, DAYBORN, YEARBORN AND CURRENTAGE */
    /* FIRST USE A SIMPLE, HARDCODED VALUE FOR ENCRYPTION, THEN MAKE IT MORE COMPLEX */
    //use a different method of encryption for the ints
    
    char IntKey = 'z';
    
    Input ^= IntKey;
    
    return Input;
}

void SaveContactBookAndSettings(vector <PersonalInformation> &CV, const char Path[], int & SpeedSelectionChoice)
{
    ofstream FileOut;
    
    
    FileOut.open(Path);
    
    if (FileOut.fail())//check to see if file opened
        cout << "Couldn't Open File\n";
    
    FileOut << "Speed Selection Choice: ";
    
    FileOut << SpeedSelectionChoice << endl;
    
    /* SAVE NUMBER OF CONTACTS TO .TXT FILE SO WE KNOW HOW MANY WE ARE READING IN IN THE REBUILD FUNCTION */
    
    FileOut << "Number of Contacts: ";
    
    FileOut << CV.size() << endl << endl;
    
    for (int i = 0; i < CV.size(); i++)
    {
        /* ENCRYPTION FOR VECTORS HAPPENS IN PRINTSTRINGSTRUCT... FUNCTIONS */
        
        PrintStringInStructDataVectorToFile(CV[i].FirstNameVector, FileOut);
        
        PrintStringInStructDataVectorToFile(CV[i].LastNameVector, FileOut);
        
        PrintStringInStructDataVectorToFile(CV[i].AddressVector, FileOut);
        
        PrintStringInStructDataVectorToFile(CV[i].PhoneNumberVector, FileOut);
        
        PrintStringInStructDataVectorToFile(CV[i].DateOfBirth, FileOut);
        
        /* ENCRYPTION FOR INTS HAPPENS RIGHT HERE */
        
        FileOut << EncryptDecryptInt(CV[i].CurrentAge) << endl;
        
        FileOut << EncryptDecryptInt(CV[i].MonthBorn) << endl;
        
        FileOut << EncryptDecryptInt(CV[i].DayBorn) << endl;
        
        FileOut << EncryptDecryptInt(CV[i].YearBorn);
        
        FileOut << "\n\n";
    }
    
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