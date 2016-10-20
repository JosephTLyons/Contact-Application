#include <fstream>    //for reading from and saving to files
#include <iostream>   //for input / output
#include <string.h>   //for strcat function in pathway commands
#include <sys/stat.h> //for mkdir functions

#include "dynamicBirthdayFunctions.hpp"

#include "readAndWriteFunctions.hpp"
#include "encryptDecryptFunctions.hpp"
#include "miscellaneousFunctions.hpp"
#include "savingFunctions.hpp"

using namespace std;

void RebuildContactBook(vector <personalInformation> &ContactVect, const char Path[], int &SpeedSelectionChoice, bool &EncryptionMode)//not cleaned up
{
    personalInformation Temporary;
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

void CreateFolderAndTextFile(char FullPath[])//not cleaned up - make full path a string in order to adjust size dynamically?
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

void ClearDataVectorsFromStructure(personalInformation &TemporaryStorage)//not cleaned up
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
