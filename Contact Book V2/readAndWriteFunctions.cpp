#include <ctype.h>    //for toupper function
#include <iostream>   //for input/output stream
#include <fstream>    //for reading from and saving to files

#include "readAndWriteFunctions.hpp"

#include "encryptDecryptFunctions.hpp"

using namespace std;

void printVectorToFile(const vector<char> &contactVect, ofstream &fileOut, const bool &encryptionMode)//not cleaned up
{
    for (int i = 0; i < contactVect.size(); i++)
    {
        if (encryptionMode == true)
            fileOut << encryptDecryptChar(contactVect[i]);
        
        else
            fileOut << contactVect[i];
    }
} // printVectorToFile()

void printVectorToScreen(const vector<char> &contactVect)//not cleaned up
{
    for (int i = 0; i < contactVect.size(); i++)
    {
        cout << contactVect[i];
    }
} // printVectorToScreen

void insertStringInVectorFromFile(vector<char> &contactVect, ifstream &fileIn, const bool &encryptionMode)//not cleaned up
{
    char insert = 1;//used for inserting characters into individual struct vectors
    //initialized at 1 to allow while loop to execute
    
    while (insert != '\n')
    {
        fileIn.get(insert);
        
        if (encryptionMode == true)
            insert = encryptDecryptChar(insert);
        
        contactVect.push_back(insert);
    }
} // insertStringInVectorFromFile()

void insertStringDataVectorFromKeyboard(vector<char> &contactVect)//not cleaned up
{
    char insert = 0;//used for inserting characters into individual struct vectors
    //initialized at 0 to allow while loop to execute
    
    char nameOfEmptyField[] = {"N/A\n"};
    
    while (insert != '\n')
    {
        cin.get(insert);//using cin.get, and not cin >>, so it stores the newline in insert - allows to break out of loop
        
        contactVect.push_back(insert);
    }
    
    if (contactVect.size() <= 1)//if theres nothing in vector or just a newline, add "N/A" text in field
    {
        contactVect.erase(contactVect.begin());//erase newline stored
        
        for (int i = 0; nameOfEmptyField[i] != 0; i++)
        {
            contactVect.push_back(nameOfEmptyField[i]);//insert text for "N/A"
        }
    }
    
    while (contactVect[0] == ' ')//remove any leading whitespace from vector
        contactVect.erase(contactVect.begin());//while first element is a space, delete first element
    
    if (!isnumber(contactVect[0]))
        (contactVect[0] = toupper(contactVect[0]));//if not a number, always capitalize (for first name and last names)
} // insertStringDataVectorFromKeyboard
