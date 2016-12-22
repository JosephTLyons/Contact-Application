#include <iostream>   //for input/output stream
#include <vector>     //for using vectors

#include "personalinformation.hpp"
#include "mainMenuFunctions.hpp"
#include "miscellaneousFunctions.hpp"
#include "userSettingFunctions.hpp"
#include "savingFunctions.hpp"

using namespace std;

int main()
{
    vector <personalInformation> contactVector;//holds all contacts
    static int mainMenuPauseCounter = 0;//pauses main menu and waits for user to press enter
    char fullPath[180] = {0};//holds the pathway to the .txt file that saves the information
    int switchChoice;
    int displaySpeed;
    int speedSelectionChoice = 2;//default medium speed setting / when program is first ran
    bool encryptionMode;
    bool lastNameFirst = true; // by default, contacts are sorted last name first
    //-------------------
    
    // CREATE THE LYONS' DEN LABS FOLDER AND TEXT FILE IN APPLICATOIN SUPPORT FOLDER IN LIBRARY
    createFolderAndSettingsFile(fullPath);
    
    // CHECK TO SEE IF FILE EXISTS AND HAS INFORMATION IN IT, IF SO, REBUILD THE LIST
    if(FileExistsAndContainsInformation(fullPath))
    {
        // Restore contacts
        rebuildContactBook(contactVector, fullPath, speedSelectionChoice, encryptionMode);
        
        // Restore user settings
        obtainSpeedSettingNumericalValues(displaySpeed, speedSelectionChoice);
    }
    
    do
    {
        // Pauses the program before displaying the main menu again on second time and after
        if (mainMenuPauseCounter++ > 0)
        {
            cout << "Press enter to go back to main menu: ";
            cin.ignore();//pause the program, wait for user to press enter
            
            cout << "\n======================\n";
        }
        
        displayMainMenuOptions(contactVector.size());
        
        cin >> switchChoice;
        cin.ignore();//ignore newline in buffer after cin >> statement
        
        cout << "\n";
        
        switch (switchChoice)
        {
            case 1:
            {
                displayAllContacts(contactVector, displaySpeed);
                break;
            }
                
            case 2:
            {
                addContact(contactVector, lastNameFirst);
                saveContactBookAndSettings(contactVector, fullPath, speedSelectionChoice, encryptionMode);
                break;
            }
                
            case 3:
            {
                editExistingContact(contactVector, displaySpeed, lastNameFirst);
                saveContactBookAndSettings(contactVector, fullPath, speedSelectionChoice, encryptionMode);
                break;
            }
                
            case 4:
            {
                searchForContacts(contactVector, displaySpeed);
                break;
            }
                
            case 5:
            {
                deleteContact(contactVector, displaySpeed);
                saveContactBookAndSettings(contactVector, fullPath, speedSelectionChoice, encryptionMode);
                break;
            }
                
            case 6:
            {
                deleteAllContacts(contactVector);
                saveContactBookAndSettings(contactVector, fullPath, speedSelectionChoice, encryptionMode);
                break;
            }
                
            case 7:
            {
                displaySettingsMenu(contactVector, displaySpeed, speedSelectionChoice, encryptionMode, lastNameFirst);
                saveContactBookAndSettings(contactVector, fullPath, speedSelectionChoice, encryptionMode);
                break;
            }
                
            case 8:
            {
                // End the program
                break;
            }
                
            default:
            {
                cout << "Not a valid choice.\n";
                main();
            }
        }
    }
    while (switchChoice != 8);
} // main()
