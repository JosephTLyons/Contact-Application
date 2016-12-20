
#include <fstream>    //for reading from and saving to files
#include <iostream>   //for input / output
#include <string>     //for using strings
#include <sys/stat.h> //for mkdir functions

#include "dynamicBirthdayFunctions.hpp"
#include "encryptDecryptFunctions.hpp"

#include "mainMenuFunctions.hpp"

#include "miscellaneousFunctions.hpp"
#include "readAndWriteFunctions.hpp"
#include "savingFunctions.hpp"

using namespace std;

void rebuildContactBook(vector<personalInformation> &contactVect, const char *path,
                        int &speedSelectionChoice, bool &encryptionMode)//not cleaned up
{
    personalInformation temporary;
    int amountOfContactsInFile;
    
    ifstream fileIn;
    
    fileIn.open(path);
    
    /* CHECK TO SEE IF FILE OPENS */
    
    if (fileIn.fail())
    {
        cout << "Couldn't Open File\n";
        return;
    }

    readInUserSettings(speedSelectionChoice, encryptionMode, amountOfContactsInFile, fileIn);

    for (int i = 0; contactVect.size() < amountOfContactsInFile; i++)
    {
        /* DECRYPTION FOR VECTORS HAPPENS IN INSERTSTRINGIN... FUNCTIONS */

        insertStringInVectorFromFile(temporary.firstNameVector, fileIn, encryptionMode);

        insertStringInVectorFromFile(temporary.lastNameVector, fileIn, encryptionMode);

        insertStringInVectorFromFile(temporary.addressVector, fileIn, encryptionMode);

        insertStringInVectorFromFile(temporary.phoneNumberVector, fileIn, encryptionMode);

        insertStringInVectorFromFile(temporary.dateOfBirthVector, fileIn, encryptionMode);
        
        /* DECRYPTION FOR INTS HAPPENS RIGHT HERE */
        
        fileIn >> temporary.currentAge;
        temporary.currentAge = encryptDecryptInt(temporary.currentAge, encryptionMode);
        
        fileIn >> temporary.monthBorn;
        temporary.monthBorn = encryptDecryptInt(temporary.monthBorn, encryptionMode);
        
        fileIn >> temporary.dayBorn;
        temporary.dayBorn = encryptDecryptInt(temporary.dayBorn, encryptionMode);
        
        fileIn >> temporary.yearBorn;
        temporary.yearBorn = encryptDecryptInt(temporary.yearBorn, encryptionMode);
        
        /* AUTOMATICALLY RECALCULATE CURRENT YEAR EVERY TIME LIST IS REBUILT */
        
        temporary.currentAge = calculateCurrentAge(temporary, temporary.monthBorn, temporary.dayBorn, temporary.yearBorn);
        
        contactVect.push_back(temporary);

        emptyVectorsInStruct(temporary);
        
        fileIn.ignore(2);//ignore two newlines between contacts (two newlines because last item is an int and doesn't store the newline like the vectors do)
    }
    
    /* SAVED CONTACTS AFTER READING IN CASE AGES WERE UPDATED AFTER RE-CALCULATING CURRENT AGE */

    saveContactBookAndSettings(contactVect, path, speedSelectionChoice, encryptionMode);
    
    fileIn.close();
}

void readInUserSettings(int &speedSelectionChoice, bool &encryptionMode,
                        int &amountOfContactsInFile, ifstream &fileIn)
{
    fileIn.ignore(15);//ignore "Security Mode: " text

    fileIn >> encryptionMode;

    fileIn.ignore(24);//ignore "Speed Selection Choice: " text

    fileIn >> speedSelectionChoice;

    fileIn.ignore();// ignore single newline between numbers

    fileIn.ignore(20);// ignore "Number of Contacts: " text

    amountOfContactsInFile = fileIn.get() - 48;// convert from char to number

    fileIn.ignore(2);// ignore two newlines after

} // rebuildContactBook()

void createFolderAndSettingsFile(char *fullPath)//not cleaned up - make full path a string in order to adjust size dynamically?
{
    //optaining pathway on mac / making my custom folder - consider another implementation that uses vector?
    
    const char *homeAndUserNamePath = getenv("HOME");//get home/username path - finds username
    const char *morePath = "/Library/Application Support/The Lyons' Den Labs";
    const char *restOfPath = "/TheLyons'DenContactInformation2.txt";
    
    strcat(fullPath, homeAndUserNamePath);
    strcat(fullPath, morePath);
    
    mkdir(fullPath, ACCESSPERMS);//make The Lyons' Den Labs folder
    
    strcat(fullPath, restOfPath);
} // createFolderAndSettingsFile()

bool checkIfFileExistsAndContainsInformation(const char *path)//shouldn't be declaring a new variable, should be passing it in, but that would call for a major rewrite of the menu function and all the function parameters//not cleaned up
{
    ifstream fileIn;
    
    fileIn.open(path);
    
    // CHECK TO MAKE SURE FILE OPENED AND CHECK TO SEE IF FILE IS EMPTY
    if ((fileIn.fail()) || (fileIn.peek() == EOF))
    {
        fileIn.close();
        return false;
    }

    // ONLY RETURN TRUE IF BOTH PREVIOUS CONDITIONS ARE NOT MET
    else
    {
        fileIn.close();
        return true;
    }
} // checkIfFileExistsAndContainsInformation()

void emptyVectorsInStruct(personalInformation &temporaryStorage)//not cleaned up
{
    deleteVectorMemoryAndClear(temporaryStorage.firstNameVector);
    deleteVectorMemoryAndClear(temporaryStorage.lastNameVector);
    deleteVectorMemoryAndClear(temporaryStorage.addressVector);
    deleteVectorMemoryAndClear(temporaryStorage.phoneNumberVector);
    deleteVectorMemoryAndClear(temporaryStorage.dateOfBirthVector);
    
} // emptyVectorsInStruct()

void deleteVectorMemoryAndClear(vector<char> &vect)
{
    /* GET BACK THE MEMORY THAT WAS ASSIGNED TO THESE VECTORS */
    /* USING SWAP METHOD ON VECTORS AS DESCRIBED IN MY STACK EXCHANGE QUESTION BELOW */
    /* http://stackoverflow.com/questions/39090554/questions-about-vectors-and-deleting-memory-associated-with-them?noredirect=1#comment65529507_39090554 */
    
    vector<char>().swap(vect);
} // deleteVectorMemoryAndClear()

void searchForContacts(const vector<personalInformation> &contactVect, const int &displaySpeed)
{
    vector<char> criteriaToSearchFor;
    
    bool criteriaFound   = false;
    bool contactsPrinted = false;
    
    cout << "Search criteria: ";
    insertStringDataVectorFromKeyboard(criteriaToSearchFor);
    cout << "\n\n";
    
    // Look through all contacs
    for (int i = 0; i < contactVect.size(); i++)
    {
        criteriaFound = searchContactsBasedOnCriteria(contactVect[i], criteriaToSearchFor);
        
        // Display found contact/s or no contacts found
        if (criteriaFound == true)
        {
            printSingleContact(contactVect, i, displaySpeed);
            contactsPrinted = true;
        }
    }
    
    if (contactsPrinted == false)
    {
        cout << "No contacts found with this criteria.\n\n";
    }
} // searchForContacts()

bool searchContactsBasedOnCriteria(const personalInformation &contact,
                                   const vector<char> criteriaToSearchFor)
{
    // Last name check
    if (vectorsAreSame(contact.lastNameVector, criteriaToSearchFor))
        return true;
    
    // First name check
    if (vectorsAreSame(contact.firstNameVector, criteriaToSearchFor))
        return true;
    
    else
        return false;
}

bool vectorsAreSame(const vector<char> &contact, const vector<char> &search)
{
    // Check each letter, but at the uppercase level so all text is the same
    // - 1 so that we dont count the newline in the vector
    for (int i = 0; i < search.size() - 1; i++)
    {
        if (toupper(contact[i]) != toupper(search[i]))
            return false;
    }
    
    return true;
}


