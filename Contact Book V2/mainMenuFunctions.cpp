#include <ctype.h>    //for toupper function
#include <iostream>   //for input/output stream
#include <unistd.h>   //for usleep functions
#include <vector>     //for using vectors

#include "mainMenuFunctions.hpp"

#include "personalInformation.hpp"
#include "readAndWriteFunctions.hpp"
#include "dynamicBirthdayFunctions.hpp"
#include "miscellaneousFunctions.hpp"
#include "userSettingFunctions.hpp"

// Simply displays the options for the main menu
void displayMainMenuOptions(const long int &numberOfContacts)
{
    cout << "(1) Display Contacts (" << numberOfContacts << ")";
    cout << "\n(2) Add Contact";
    cout << "\n(3) Edit Existing Contact";
    cout << "\n(4) Search for a Contact";
    cout << "\n(5) Delete Contact";
    cout << "\n(6) Delete All Contacts";
    cout << "\n(7) Settings and Configuration";
    cout << "\n(8) Exit";
    
    cout << "\n\nChoice: ";
} // displayMainMenuOptions()

/*
 This function displays all the contacts, and related information,
 that are within the personalInformation vector.
*/
void displayAllContacts(const vector<personalInformation> &contactVect, const int &displaySpeed)
{
    printDividingLine();
    
    for (int vectorPosition = 0; vectorPosition < contactVect.size(); vectorPosition++)
    {
        printSingleContact(contactVect, vectorPosition, displaySpeed);
    }
    
    // IF THERE ARE NO CONTACTS, DISPLAY CONTACT BOOK IS EMPTY
    if (contactVect.size() == 0)
        cout << "Contact Book is empty.\n\n";
    
    printDividingLine();
} // displayAllContacts()

void printDividingLine()
{
    cout << "======================\n\n";
} // printDividingLine()

void printSingleContact(const vector<personalInformation> &contactVect,
                        const int &vectorPos, const int &displaySpeed)
{
    cout << "Contact Number: " << vectorPos+1;
    
    displayVectors(contactVect, vectorPos);

    // IF BIRTHDAY IS LESS THAN 7 DAYS AWAY, DISPLAY THAT INFORMATION TO THE SCREEEN
    daysUntilBirthday(contactVect, vectorPos);
    
    cout << "\n\n";
    
    usleep(displaySpeed);
} // printContactToFile()

void displayVectors(const vector<personalInformation> &contactVect, const int &vectorPos)
{
    cout << "\nFirst Name:     ";
    printVectorToScreen(contactVect[vectorPos].firstNameVector);

    cout << "Last Name:      ";
    printVectorToScreen(contactVect[vectorPos].lastNameVector);

    cout << "Address:        ";
    printVectorToScreen(contactVect[vectorPos].addressVector);

    cout << "Phone Number:   ";
    printVectorToScreen(contactVect[vectorPos].phoneNumberVector);

    cout << "Date Of Birth:  ";
    printVectorToScreen(contactVect[vectorPos].dateOfBirthVector);

    displayAge(contactVect, vectorPos);
} // printContactToFile()

void displayAge(const vector<personalInformation> &contactVect, const int &vectorPos)
{
    /* ONLY DISPLAY CURRENT AGE IF N/A ISN'T IN DATEOFBIRTH FIELD */
    
    if (contactVect[vectorPos].dateOfBirthVector[0] != 'N')
    {
        if (contactVect[vectorPos].dateOfBirthVector[1] != '/')
        {
            if (contactVect[vectorPos].dateOfBirthVector[2] != 'A')
            {
                cout << "Current Age:    ";
                cout << contactVect[vectorPos].currentAge;
            }
        }
    }
} // displayAge()

void daysUntilBirthday(const vector<personalInformation> &contactVect, const int &vectorPos)
{
    /* IF BIRTHDAY IS LESS THAN 7 DAYS AWAY, DISPLAY THAT INFORMATION TO THE SCREEEN */
    
    if (contactVect[vectorPos].birthdayIsInXDays >= 0 && contactVect[vectorPos].birthdayIsInXDays <= 7)
        cout << "\n*BIRTHDAY IS IN " << contactVect[vectorPos].birthdayIsInXDays << " DAYS*";
} // daysUntilBirthday()

void addContact(vector<personalInformation> &contactVect)//not cleaned up
{
    personalInformation temporary;//temporary holding spot for input, used to store in vector
    char userChoice;
    
    while (toupper(userChoice) != 'N' && toupper(userChoice) != 'Q')
    {
        getContactInfoFromUser(temporary);

        contactVect.push_back(temporary);//store Temp in ContactVector Vector

        emptyVectorsInStruct(temporary);
        
        if (contactVect.size() > 1)//don't go into sort function if only one contact is in vector
            sortContactVector(contactVect);
        
        cout << "\nAdd another contact? Y/N: ";
        cin >> userChoice;
        
        if (toupper(userChoice) == 'Y')//dont cin.ignore() if user doesn't repeat loop, used to keep main from pausing too many times
            cin.ignore();//clear newline from cin >> statement above
        
        cout << "\n";
    }
    
    cin.ignore();//removes 1 newline at the end of this function - needed for main loop to work correctly
} // addContact()

void getContactInfoFromUser(personalInformation &temporary)
{
    cout << "Enter First Name:   ";
    insertStringDataVectorFromKeyboard(temporary.firstNameVector);

    cout << "Enter Last Name:    ";
    insertStringDataVectorFromKeyboard(temporary.lastNameVector);

    cout << "Enter Address:      ";
    insertStringDataVectorFromKeyboard(temporary.addressVector);

    cout << "Enter Phone Number: ";
    insertStringDataVectorFromKeyboard(temporary.phoneNumberVector);

    cout << "Enter Birthday:";

    temporary.currentAge = birthDayInput(temporary);
}

void editExistingContact(vector<personalInformation> &contactVect, const int &displaySpeed)//not cleaned up
{
    int contactNumberToEdit;
    char fieldToEdit = 0;

    displayAllContacts(contactVect, displaySpeed);
    
    cout << "Which contact would you like to edit: ";
    cin >> contactNumberToEdit;
    cin.ignore();//remove newline left over from cin >> statement above
    
    contactNumberToEdit--;//decrement value here to work with vector/array notation
    
    if (contactNumberToEdit < contactVect.size())//error will occur if tries to erase number outside of vector bound
    {
        cout << "\n\nContact you wish to edit: ";

        printVectorToScreen(contactVect[contactNumberToEdit].firstNameVector);
        
        cout << "\nPress enter to skip editing a field.";
        cout << "\nPress \"Y\" + enter to edit a field.";
        
        cout << "\n\n======================\n\n";
        
        cout << "Original First Name:    ";
        printVectorToScreen(contactVect[contactNumberToEdit].firstNameVector);
        
        cout << "Edit Field?: ";
        cin.get(fieldToEdit);//using cin.get() so that newlines are stored
        
        if (toupper(fieldToEdit) == 'Y')
        {
            cin.ignore();//clear left over newline in input buffer
            
            deleteVectorMemoryAndClear(contactVect[contactNumberToEdit].firstNameVector);
            
            cout << "\nEnter New First Name:   ";
            insertStringDataVectorFromKeyboard(contactVect[contactNumberToEdit].firstNameVector);
            
            fieldToEdit = 0;//reset back to zero so next if condition isn't automatically met
        }
        
        cout << "\nOriginal Last Name:     ";
        printVectorToScreen(contactVect[contactNumberToEdit].lastNameVector);
        
        cout << "Edit Field?: ";
        cin.get(fieldToEdit);//using cin.get() so that newlines are stored
        
        if (toupper(fieldToEdit) == 'Y')
        {
            cin.ignore();//clear left over newline in input buffer
            
            deleteVectorMemoryAndClear(contactVect[contactNumberToEdit].lastNameVector);
            
            cout << "\nEnter New Last Name:    ";
            insertStringDataVectorFromKeyboard(contactVect[contactNumberToEdit].lastNameVector);
            
            fieldToEdit = 0;//reset back to zero so next if condition isn't automatically met
        }
        
        cout << "\nOriginal Address:       ";
        printVectorToScreen(contactVect[contactNumberToEdit].addressVector);
        
        cout << "Edit Field?: ";
        cin.get(fieldToEdit);//using cin.get() so that newlines are stored
        
        if (toupper(fieldToEdit) == 'Y')
        {
            cin.ignore();//clear left over newline in input buffer
            
            deleteVectorMemoryAndClear(contactVect[contactNumberToEdit].addressVector);
            
            cout << "\nEnter New Address:      ";
            insertStringDataVectorFromKeyboard(contactVect[contactNumberToEdit].addressVector);
            
            fieldToEdit = 0;//reset back to zero so next if condition isn't automatically met
        }
        
        cout << "\nOriginal Phone Number:  ";
        printVectorToScreen(contactVect[contactNumberToEdit].phoneNumberVector);
        
        cout << "Edit Field?: ";
        cin.get(fieldToEdit);//using cin.get() so that newlines are stored
        
        if (toupper(fieldToEdit) == 'Y')
        {
            cin.ignore();//clear left over newline in input buffer
            
            deleteVectorMemoryAndClear(contactVect[contactNumberToEdit].phoneNumberVector);
            
            cout << "\nEnter New Phone Number: ";
            insertStringDataVectorFromKeyboard(contactVect[contactNumberToEdit].phoneNumberVector);
            
            fieldToEdit = 0;//reset back to zero so next if condition isn't automatically met
        }
        
        cout << "\nOriginal Date of Birth: ";
        printVectorToScreen(contactVect[contactNumberToEdit].dateOfBirthVector);
        
        cout << "Edit Field?: ";
        cin.get(fieldToEdit);//using cin.get() so that newlines are stored
        
        if (toupper(fieldToEdit) == 'Y')
        {
            cin.ignore();//clear left over newline in input buffer
            
            deleteVectorMemoryAndClear(contactVect[contactNumberToEdit].dateOfBirthVector);
            
            cout << "\nEnter New Date of Birth:";
            contactVect[contactNumberToEdit].currentAge = birthDayInput(contactVect[contactNumberToEdit]);
            
            fieldToEdit = 0;//reset back to zero so next if condition isn't automatically met
        }
        
        cout << "\n\n======================\n\n";
    }

    sortContactVector(contactVect);
} // editExistingContact

void deleteContact(vector<personalInformation> &contactVect, const int &displaySpeed)//not cleaned up
{
    int contactNumberToDelete;
    char confirmDelete = 0;
    char deleteAnotherContactChoice;
    
    do
    {
        displayAllContacts(contactVect, displaySpeed);//display list again
        
        cout << "Type in the number of the contact you wish to delete: ";
        cin >> contactNumberToDelete;
        
        if (contactNumberToDelete >= 0 && contactNumberToDelete <= contactVect.size())//error will occur if tries to erase number outside of vector bound
        {
            contactNumberToDelete--;//decrement to work with vector/array notation
            
            cout << "\nYou are trying to delete: ";
            
            cout << "\n\n======================\n\n";
            
            displayVectors(contactVect, contactNumberToDelete);
            
            cout << "\n======================\n\n";
            
            cout << "\nAre you sure you want to delete ";
            
            //display name of contact being deleted
            for (int i = 0; contactVect[contactNumberToDelete].firstNameVector[i] != '\n'; i++)            {
                cout << contactVect[contactNumberToDelete].firstNameVector[i];
            }
            
            cout << "? Y/N: ";
            cin >> confirmDelete;
            
            if (toupper(confirmDelete) == 'Y')
                contactVect.erase(contactVect.begin() + contactNumberToDelete);
        }
        
        else
            cout << "\nNo contact located at this number";
        
        if (toupper(confirmDelete) == 'N' && ++contactNumberToDelete <= contactVect.size())//increment Contact to work properly with size()function
            cout << "\nNo contact deleted.";//if user chooses to not delete the contact
        
        cout << "\n\nDelete another contact? Y/N: ";
        cin >> deleteAnotherContactChoice;
        cin.ignore();//removes 1 newline at the end of this function - needed for main loop to work correctly
    }
    while (toupper(deleteAnotherContactChoice) == 'Y' && contactVect.size() > 0);//don't try to delete when nothing is left in vector
    
    cout << "\n\n";
} // deleteContact()

void deleteAllContacts(vector<personalInformation> &contactVect)//not cleaned up
{
    vector<char> userChoice;
    bool contactsNotDeletedFlag = true;
    char insert = 1; //initialized at 1 to allow while loop to execute
    
    cout << "Are you sure you'd like to delete all contacts? Type \"YES\" to confirm (Must be a capital YES): ";
    
    do
    {
        cin.get(insert);
        userChoice.push_back(insert);
    }
    while (insert != '\n');

    if (userWantsToDelete(userChoice))
    {
        contactsNotDeletedFlag = false;
        
        // Using swap method to clear and deallocate memory in contactVect
        vector<personalInformation>().swap(contactVect);
        
        cout << endl << endl << contactVect.size() << endl;
        
        cout << "\nAll contacts have been deleted.\n\n";
    }

    if (contactsNotDeletedFlag == true)
        cout << "\nContacts were not deleted.\n\n";
} // deleteAllContacts()

bool userWantsToDelete(const vector<char> &userChoice)
{
    if((userChoice[0] == 'Y') &&
       (userChoice[1] == 'E') &&
       (userChoice[2] == 'S'))
        
        return true;
    
    else
        return false;
} // userWantsToDelete()

void displaySettingsMenu(const vector<personalInformation> &contactVect, int &displaySpeed,
                         int &speedSelectionChoice, bool &encryptionMode)//not cleaned up
{
    int choice;
    
    do
    {
        cout <<   "(1) Display Scroll Speed";
        cout << "\n(2) Encryption";
        cout << "\n(3) Quit and Save Settings";
        
        cout << "\n\nchoice: ";
        cin >> choice;
        
        switch (choice)
        {
            case 1:
                scrollSpeedSettingsAndUserInput(contactVect, displaySpeed, speedSelectionChoice);
                break;
                
            case 2:
                encryptionOnOffSetting(encryptionMode);
                break;
                
            default:
                break;
        }
    }
    while (choice >= 1 && choice <= 2);
    
    cout << endl;
} // displaySettingsMenu()
