#include <ctype.h>    //for isspace function in getIntSetting() function
#include <fstream>    //for reading from and saving to files
#include <iostream>   //for input / output
#include <sys/stat.h> //for mkdir functions

#include "dynamicBirthdayFunctions.hpp"
#include "encryptDecryptFunctions.hpp"

#include "miscellaneousFunctions.hpp"

#include "readAndWriteFunctions.hpp"
#include "savingFunctions.hpp"

using namespace std;

void rebuildContactBook(vector<personalInformation> &contactVect, const char *path,
                        int &speedSelectionChoice, bool &encryptionMode, bool &lastNameFirst)//not cleaned up
{
    personalInformation temporary;
    int amountOfContactsInFile;
    
    ifstream fileIn;
    
    fileIn.open(path);
    
    // CHECK TO SEE IF FILE OPENS
    if (fileIn.fail())
    {
        cout << "Couldn't Open File\n";
        return;
    }

    readInUserSettings(speedSelectionChoice, encryptionMode,
                       amountOfContactsInFile, lastNameFirst, fileIn);

    for (int i = 0; contactVect.size() < amountOfContactsInFile; i++)
    {
        // Decryption for vectors happens in insertStringInVectorFromFile funcionts
        insertStringInVectorFromFile(temporary.firstNameVector, fileIn, encryptionMode);
        insertStringInVectorFromFile(temporary.lastNameVector, fileIn, encryptionMode);
        insertStringInVectorFromFile(temporary.addressVector, fileIn, encryptionMode);
        insertStringInVectorFromFile(temporary.phoneNumberVector, fileIn, encryptionMode);
        insertStringInVectorFromFile(temporary.dateOfBirthVector, fileIn, encryptionMode);
        
        // Read in integers
        fileIn >> temporary.currentAge;
        fileIn >> temporary.monthBorn;
        fileIn >> temporary.dayBorn;
        fileIn >> temporary.yearBorn;
        
        // If encrypted, decrypt
        if (encryptionMode == true)
        {
            temporary.currentAge = encryptDecryptInt(temporary.currentAge);
            temporary.monthBorn = encryptDecryptInt(temporary.monthBorn);
            temporary.dayBorn = encryptDecryptInt(temporary.dayBorn);
            temporary.yearBorn = encryptDecryptInt(temporary.yearBorn);
        }
        
        // AUTOMATICALLY RECALCULATE CURRENT YEAR EVERY TIME LIST IS REBUILT
        temporary.currentAge = calculateCurrentAge(temporary, temporary.monthBorn,
                                                   temporary.dayBorn, temporary.yearBorn);
        
        contactVect.push_back(temporary);

        emptyVectorsInStruct(temporary);
        
        fileIn.ignore(2);//ignore two newlines between contacts (two newlines because last item is an int and doesn't store the newline like the vectors do)
    }
    
    /* SAVED CONTACTS AFTER READING IN CASE AGES WERE UPDATED AFTER RE-CALCULATING CURRENT AGE */

    saveContactBookAndSettings(contactVect, path, speedSelectionChoice, encryptionMode, lastNameFirst);
    
    fileIn.close();
}

void readInUserSettings(int &speedSelectionChoice, bool &encryptionMode,
                        int &amountOfContactsInFile, bool &lastNameFirst, ifstream &fileIn)
{
    // 15 = ignore "Security Mode: "          text
    encryptionMode         = getBoolSetting(fileIn, 15);

    // 24 = ignore "Speed Selection Choice: " text
    speedSelectionChoice   = getIntSetting(fileIn, 24);
    
    // 19 = ignore "Sort by Last Name: "      text
    lastNameFirst          = getBoolSetting(fileIn, 19);

    // 20 = ignore "Number of Contacts: "     text
    amountOfContactsInFile = getIntSetting(fileIn, 20);
    
    fileIn.ignore();// ignore empty newline after settings

} // rebuildContactBook()

bool getBoolSetting(ifstream &fileIn, int ignoreCount)
{
    bool setting;
    
    fileIn.ignore(ignoreCount);//ignore text
    
    setting = fileIn.get() - 48; // convert character to number
    
    fileIn.ignore();// ignore single newline that isn't removed because using fileIn.get()
    
    return setting;
} // getBoolSetting()

int getIntSetting(ifstream &fileIn, int ignoreCount)
{
    int setting = 0;
    
    fileIn.ignore(ignoreCount);//ignore text
    
    // Extract full number from file as long as the next char isn't whitespace
    while (!isspace(fileIn.peek()))
    {
        setting *= 10;
        setting += fileIn.get() - 48; // convert character to number
    }
    
    fileIn.ignore();// ignore single newline that isn't removed because using fileIn.get()
    
    return setting;
} // getIntSetting()

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

bool FileExistsAndContainsInformation(const char *path)//shouldn't be declaring a new variable, should be passing it in, but that would call for a major rewrite of the menu function and all the function parameters//not cleaned up
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
    // GET BACK THE MEMORY THAT WAS ASSIGNED TO THESE VECTORS
    // USING SWAP METHOD ON VECTORS AS DESCRIBED IN MY STACK EXCHANGE QUESTION BELOW
    // http://stackoverflow.com/questions/39090554/questions-about-vectors-and-deleting-memory-associated-with-them?noredirect=1#comment65529507_39090554
    
    vector<char>().swap(vect);
} // deleteVectorMemoryAndClear()

