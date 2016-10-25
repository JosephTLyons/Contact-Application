#include <iostream>   //for input/output stream
#include <vector>     //for using vectors

#include "personalinformation.hpp"
#include "mainMenuFunctions.hpp"
#include "miscellaneousFunctions.hpp"
#include "userSettingFunctions.hpp"
#include "savingFunctions.hpp"

using namespace std;

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
    vector <personalInformation> contactVector;//holds all contacts
    static int mainMenuPauseCounter = 0;//pauses main menu and waits for user to press enter
    char fullPath[180] = {0};//holds the pathway to the .txt file that saves the information
    int switchChoice;//
    int displaySpeed;
    int speedSelectionChoice = 2;//default medium speed setting / when program is first ran
    bool encryptionMode;
    //-------------------
    
    /* CREATE THE LYONS' DEN LABS FOLDER AND TEXT FILE IN APPLICATOIN SUPPORT FOLDER IN LIBRARY */

    createFolderAndTextFile(fullPath);
    
    /* CHECK TO SEE IF FILE EXISTS AND HAS INFORMATION IN IT, IF SO, REBUILD THE LIST */
    
    if(checkIfFileExistsAndContainsInformation(fullPath))
    {
        rebuildContactBook(contactVector, fullPath, speedSelectionChoice, encryptionMode);//restore contacts
        obtainSpeedSettingNumericalValues(displaySpeed, speedSelectionChoice);//restore user settings
    }
    
    do
    {
        //pauses the program before displaying the main menu again on second time and after
        if (mainMenuPauseCounter++ > 0)
        {
            cout << "Press enter to go back to main menu: ";
            cin.ignore();//pause the program, wait for user to press enter
            
            cout << "\n======================\n";
        }
        
        displayMainMenuOptions();
        
        cin >> switchChoice;
        cin.ignore();//ignore newline in buffer after cin >> statement
        
        cout << "\n";
        
        switch (switchChoice)
        {
            case 1:
            {
                displayContacts(contactVector, displaySpeed);
                break;
            }
                
            case 2:
            {
                addContact(contactVector);
                saveContactBookAndSettings(contactVector, fullPath, speedSelectionChoice, encryptionMode);
                break;
            }
                
            case 3:
            {
                editExistingContact(contactVector, displaySpeed);
                saveContactBookAndSettings(contactVector, fullPath, speedSelectionChoice, encryptionMode);
                break;
            }
                
            case 4:
            {
                deleteContact(contactVector, displaySpeed);
                saveContactBookAndSettings(contactVector, fullPath, speedSelectionChoice, encryptionMode);
                break;
            }
                
            case 5:
            {
                deleteAllContacts(contactVector);
                saveContactBookAndSettings(contactVector, fullPath, speedSelectionChoice, encryptionMode);
                break;
            }
                
            case 6:
            {
                displaySettingsMenu(contactVector, displaySpeed, speedSelectionChoice, encryptionMode);
                saveContactBookAndSettings(contactVector, fullPath, speedSelectionChoice, encryptionMode);
                break;
            }
                
            default:
                break;
        }
    }
    while (switchChoice != 7);
} // main()
