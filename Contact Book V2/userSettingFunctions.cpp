#include <iostream>   //for input/output stream
#include <ctype.h>    //for toupper function

#include "userSettingFunctions.hpp"

#include "mainMenuFunctions.hpp"

using namespace std;

void encryptionOnOffSetting(bool &encryptionMode)//not cleaned up
{
    char userChoice;
    
    cout << "\nEncyption ";
    
    if (encryptionMode == true)
    {
        cout << "[on] / off";
        cout << "\n\nWould you like to turn encryption off? Y/N?: ";
        
        cin >> userChoice;
        
        if (toupper(userChoice) == 'Y')
            encryptionMode = false;
    }
    
    else
    {
        cout << "on / [off]";
        cout << "\n\nWould you like to turn encryption on? Y/N?: ";
        
        cin >> userChoice;
        
        if (toupper(userChoice) == 'Y')
            encryptionMode = true;
    }
    
    cout << endl;
} // encryptionOnOffSetting()

void scrollSpeedSettingsAndUserInput(const vector<personalInformation> &contactVect,
                                     int &displaySpeed, int &speedSelectionChoice)//not cleaned up
{
    char loopAgainOrNot = 'N';
    
    do
    {
        /* DISPLAY OPTIONS AND SHOW WHICH OPTION IS CURRENTLY SELECTED */
        
        cout << "Scrolling contact display rate: ";
        
        /* SLOW SPEED DISPLAY */
        
        cout << "\n\n(1)";
        
        if (speedSelectionChoice == 1)
            cout << " [*]";
        else
            cout << " [ ]";
        
        cout << " Slow";
        
        /* MEDIUM SPEED DISPLAY */
        
        cout << "\n(2)";
        
        if (speedSelectionChoice == 2)
            cout << " [*]";
        else
            cout << " [ ]";
        
        cout << " Medium";
        
        /* FAST SPEED DISPLAY */
        
        cout << "\n(3)";
        
        if (speedSelectionChoice == 3)
            cout << " [*]";
        else
            cout << " [ ]";
        
        cout << " Fast";
        
        
        cout << "\n(4)     Quit Settings";
        
        
        cout << "\n\n* = current option selected";
        
        cout << "\n\nSpeed Selection: ";
        
        cin >> speedSelectionChoice;

        obtainSpeedSettingNumericalValues(displaySpeed, speedSelectionChoice);
        
        cout << "Preview of Speed:\n\n";

        displayAllContacts(contactVect, displaySpeed);
        
        cout << "\nSet a different speeed? Y/N: ";
        cin >> loopAgainOrNot;
        
        cout << "\n";
        cin.ignore();//remove one left over newline
    }
    while (toupper(loopAgainOrNot) == 'Y');
} // scrollSpeedSettingsAndUserInput()

void obtainSpeedSettingNumericalValues(int &displaySpeed, const int &speedSelectionChoice)//not cleaned up
{
    /* VARIABLES THAT HOLD THE VARIOUS SPEEDS, EASY TO MODIFY THESE HERE */
    
    int slow   = 140000;
    int medium = 70000;
    int fast   = 20000;
    
    /* INPUT CHOICE OF SPEED AND STORE SPEED IN DISPLAYSPEED */
    
    if (speedSelectionChoice == 1)
        displaySpeed = slow;
    
    else if (speedSelectionChoice == 2)
        displaySpeed = medium;
    
    else
        displaySpeed = fast;
    
    //settings for displaying birthday reminders or not
} // obtainSpeedSettingNumericalValues()
