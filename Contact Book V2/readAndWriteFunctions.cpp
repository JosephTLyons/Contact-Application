#include <ctype.h>    //for toupper function
#include <iostream>   //for input/output stream
#include <fstream>    //for reading from and saving to files

#include "readAndWriteFunctions.hpp"

#include "encryptDecryptFunctions.hpp"

using namespace std;

void PrintVectorToFile(const vector <char> &ContactVect, ofstream &FileOut, const bool &EncryptionMode)//not cleaned up
{
    for (int i = 0; i < ContactVect.size(); i++)
    {
        FileOut << EncryptDecryptChar(ContactVect[i], EncryptionMode);
    }
}

void PrintVectorToScreen(const vector <char> &ContactVect)//not cleaned up
{
    for (int i = 0; i < ContactVect.size(); i++)
    {
        cout << ContactVect[i];
    }
}

void InsertStringInVectorFromFile(vector <char> &ContactVect, ifstream &FileIn, const bool &EncryptionMode)//not cleaned up
{
    char Insert = 1;//used for inserting characters into individual struct vectors
    //initialized at 1 to allow while loop to execute
    
    while (Insert != '\n')
    {
        FileIn.get(Insert);
        
        Insert = EncryptDecryptChar(Insert, EncryptionMode);
        
        ContactVect.push_back(Insert);
    }
}

void InsertStringDataVectorFromKeyboard(vector <char> &ContactVect)//not cleaned up
{
    char Insert = 0;//used for inserting characters into individual struct vectors
    //initialized at 0 to allow while loop to execute
    
    char NameOfEmptyField[] = {"N/A\n"};
    
    while (Insert != '\n')
    {
        cin.get(Insert);//using cin.get, and not cin >>, so it stores the newline in Insert - allows to break out of loop
        
        ContactVect.push_back(Insert);
    }
    
    if (ContactVect.size() <= 1)//if theres nothing in vector or just a newline, add "N/A" text in field
    {
        ContactVect.erase(ContactVect.begin());//erase newline stored
        
        for (int i = 0; NameOfEmptyField[i] != 0; i++)
        {
            ContactVect.push_back(NameOfEmptyField[i]);//insert text for "N/A"
        }
    }
    
    while (ContactVect[0] == ' ')//remove any leading whitespace from vector
        ContactVect.erase(ContactVect.begin());//while first element is a space, delete first element
    
    if (!isnumber(ContactVect[0]))
        (ContactVect[0] = toupper(ContactVect[0]));//if not a number, always capitalize (for first name and last names)
}
