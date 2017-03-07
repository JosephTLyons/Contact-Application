#include <ctime>    //for time and date functions
#include <fstream>  //for reading from and saving to files
#include <iostream> //for input/output stream

#include "savingFunctions.hpp"

#include "readAndWriteFunctions.hpp"
#include "encryptDecryptFunctions.hpp"

using namespace std;

void saveContactBookAndSettings(const vector<personalInformation> &contactVect,
                                const char *path, const int &speedSelectionChoice,
                                const bool &encryptionMode, const bool &lastNameFirst)//not cleaned up
{
    ofstream fileOut;
    
    fileOut.open(path);
    
    // Check to see if file opened
    if (fileOut.fail())
        cout << "Couldn't Open File\n";
    
    fileOut << "Security Mode: ";
    
    fileOut << encryptionMode << endl;
    
    fileOut << "Speed Selection Choice: ";
    
    fileOut << speedSelectionChoice << endl;
    
    fileOut << "Sort by Last Name: ";
    
    fileOut << lastNameFirst << endl;
    
    // SAVE NUMBER OF CONTACTS TO .TXT FILE SO WE KNOW
    // HOW MANY WE ARE READING IN IN THE REBUILD FUNCTION
    fileOut << "Number of Contacts: ";
    
    fileOut << contactVect.size() << endl << endl;
    
    for (int i = 0; i < contactVect.size(); i++)
    {
        printContactToFile(encryptionMode, i, contactVect, fileOut);
    }
    
    fileOut << "Contacts Last Altered: " << obtainDateAndTime() << endl;
    
    fileOut.close();
}

void printContactToFile(const bool &encryptionMode, int contactNumber,
                        const vector<personalInformation> &contactVect, ofstream &fileOut)
{
    // Encryption for vectors happens in printVectorToFile functions
    printVectorToFile(contactVect[contactNumber].firstNameVector, fileOut, encryptionMode);
    printVectorToFile(contactVect[contactNumber].lastNameVector, fileOut, encryptionMode);
    printVectorToFile(contactVect[contactNumber].addressVector, fileOut, encryptionMode);
    printVectorToFile(contactVect[contactNumber].phoneNumberVector, fileOut, encryptionMode);
    printVectorToFile(contactVect[contactNumber].dateOfBirthVector, fileOut, encryptionMode);

    // Encryption for ints happens here
    if (encryptionMode == true)
    {
        fileOut << encryptDecryptInt(contactVect[contactNumber].currentAge) << endl;
        fileOut << encryptDecryptInt(contactVect[contactNumber].monthBorn)  << endl;
        fileOut << encryptDecryptInt(contactVect[contactNumber].dayBorn)    << endl;
        fileOut << encryptDecryptInt(contactVect[contactNumber].yearBorn);
    }
    
    else
    {
        fileOut << contactVect[contactNumber].currentAge << endl;
        fileOut << contactVect[contactNumber].monthBorn  << endl;
        fileOut << contactVect[contactNumber].dayBorn    << endl;
        fileOut << contactVect[contactNumber].yearBorn;
    }

    fileOut << "\n\n";
} // printContactToFile()

string obtainDateAndTime()//not my code here - modified it to display what I want and to read easier
{
    char timeArray[50];
    
    time_t now = time(NULL);
    
    strftime(timeArray, 50, "%D, %I:%M %p", localtime(&now));
    
    return string(timeArray);
} // obtainDateAndTime()
