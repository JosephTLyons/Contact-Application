#include <iostream>   //for input/output stream
#include <ctype.h>    //for toupper function

#include "userSettingFunctions.hpp"

#include "mainMenuFunctions.hpp"

using namespace std;

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

void ScrollSpeedSettingsAndUserInput(const vector <personalInformation> &ContactVect, int &DisplaySpeed, int &SpeedSelectionChoice)//not cleaned up
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
