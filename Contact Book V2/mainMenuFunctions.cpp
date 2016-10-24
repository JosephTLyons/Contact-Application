#include <ctype.h>    //for toupper function
#include <iostream>   //for input/output stream
#include <unistd.h>   //for usleep functions
#include <vector>     //for using vectors

#include "readAndWriteFunctions.hpp"

#include "personalInformation.hpp"
#include "mainMenuFunctions.hpp"
#include "dynamicBirthdayFunctions.hpp"
#include "miscellaneousFunctions.hpp"
#include "userSettingFunctions.hpp"

// Simply displays the options for the main menu
void displayMainMenuOptions()
{
    cout << "(1) Display List";
    cout << "\n(2) Add Contact";
    cout << "\n(3) Edit Existing Contact";
    cout << "\n(4) Delete Contact";
    cout << "\n(5) Delete All Contacts";
    cout << "\n(6) Settings and Configuration";
    cout << "\n(7) Exit";
    
    cout << "\n\nChoice: ";
}

/*
 This function displays all the contacts, and related information,
 that are within the personalInformation vector.
*/
void DisplayContacts(const vector<personalInformation> &ContactVect, const int &DisplaySpeed)//not cleaned up
{
    printDividingLine();
    
    for (int vectorPosition = 0; vectorPosition < ContactVect.size(); vectorPosition++)
    {
        printContact(ContactVect, vectorPosition, DisplaySpeed);
    }
    
    /* IF THERE ARE NO CONTACTS, DISPLAY CONTACT BOOK IS EMPTY */
    
    if (ContactVect.size() == 0)
        cout << "Contact Book is empty.\n\n";
    
    printDividingLine();
}

void printDividingLine()
{
    cout << "======================\n\n";
}

void printContact(const vector<personalInformation> &ContactVect, const int &VectorPos,
                  const int &displaySpeed)
{
    cout << "Contact Number: " << VectorPos+1;
    cout << "\nFirst Name:     ";
    PrintVectorToScreen(ContactVect[VectorPos].FirstNameVector);
    
    cout << "Last Name:      ";
    PrintVectorToScreen(ContactVect[VectorPos].LastNameVector);
    
    cout << "Address:        ";
    PrintVectorToScreen(ContactVect[VectorPos].AddressVector);
    
    cout << "Phone Number:   ";
    PrintVectorToScreen(ContactVect[VectorPos].PhoneNumberVector);
    
    cout << "Date Of Birth:  ";
    PrintVectorToScreen(ContactVect[VectorPos].DateOfBirth);
    
    displayAge(ContactVect, VectorPos);
    
    /* IF BIRTHDAY IS LESS THAN 7 DAYS AWAY, DISPLAY THAT INFORMATION TO THE SCREEEN */
    
    daysUntilBirthday(ContactVect, VectorPos);
    
    cout << "\n\n";
    
    usleep(displaySpeed);
}

void displayAge(const vector<personalInformation> &ContactVect, const int &VectorPos)
{
    /* ONLY DISPLAY CURRENT AGE IF N/A ISN'T IN DATEOFBIRTH FIELD */
    
    if (ContactVect[VectorPos].DateOfBirth[0] != 'N')
    {
        if (ContactVect[VectorPos].DateOfBirth[1] != '/')
        {
            if (ContactVect[VectorPos].DateOfBirth[2] != 'A')
            {
                cout << "Current Age:    ";
                cout << ContactVect[VectorPos].CurrentAge;
            }
        }
    }
}

void daysUntilBirthday(const vector<personalInformation> &ContactVect, const int &VectorPos)
{
    /* IF BIRTHDAY IS LESS THAN 7 DAYS AWAY, DISPLAY THAT INFORMATION TO THE SCREEEN */
    
    if (ContactVect[VectorPos].BirthdayIsInXDays >= 0 && ContactVect[VectorPos].BirthdayIsInXDays <= 7)
        cout << "\n*BIRTHDAY IS IN " << ContactVect[VectorPos].BirthdayIsInXDays << " DAYS*";
}

void AddContact(vector <personalInformation> &ContactVect)//not cleaned up
{
    personalInformation Temporary;//temporary holding spot for input, used to store in vector
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

void EditExistingContact(vector <personalInformation> &ContactVect, const int &DisplaySpeed)//not cleaned up
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

void DeleteContact(vector <personalInformation> &ContactVect, const int &DisplaySpeed)//not cleaned up
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

void DeleteAllContacts(vector <personalInformation> &ContactVect)//not cleaned up
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

void DisplaySettingsMenu(const vector <personalInformation> &ContactVect, int &DisplaySpeed, int &SpeedSelectionChoice, bool &EncryptionMode)//not cleaned up
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
} // DisplaySettingsMenu()
