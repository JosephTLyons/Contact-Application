#include <ctime>    //for time and date functions
#include <fstream>  //for reading from and saving to files
#include <iostream> //for input/output stream

#include "savingFunctions.hpp"

#include "readAndWriteFunctions.hpp"
#include "encryptDecryptFunctions.hpp"

using namespace std;

void saveContactBookAndSettings(const vector<personalInformation> &contactVect, const char *path,
                                const int &speedSelectionChoice, const bool &encryptionMode)//not cleaned up
{
    ofstream fileOut;
    
    
    fileOut.open(path);
    
    if (fileOut.fail())//check to see if file opened
        cout << "Couldn't Open File\n";
    
    
    fileOut << "Security Mode: ";
    
    fileOut << encryptionMode << endl;
    
    fileOut << "Speed Selection Choice: ";
    
    fileOut << speedSelectionChoice << endl;
    
    /* SAVE NUMBER OF CONTACTS TO .TXT FILE SO WE KNOW HOW MANY WE ARE READING IN IN THE REBUILD FUNCTION */
    
    fileOut << "Number of Contacts: ";
    
    fileOut << contactVect.size() << endl << endl;
    
    for (int i = 0; i < contactVect.size(); i++)
    {
        /* ENCRYPTION FOR VECTORS HAPPENS IN PRINTSTRINGSTRUCT... FUNCTIONS */

        printVectorToFile(contactVect[i].firstNameVector, fileOut, encryptionMode);

        printVectorToFile(contactVect[i].lastNameVector, fileOut, encryptionMode);

        printVectorToFile(contactVect[i].addressVector, fileOut, encryptionMode);

        printVectorToFile(contactVect[i].phoneNumberVector, fileOut, encryptionMode);

        printVectorToFile(contactVect[i].dateOfBirthVector, fileOut, encryptionMode);
        
        /* ENCRYPTION FOR INTS HAPPENS RIGHT HERE */
        
        fileOut << encryptDecryptInt(contactVect[i].currentAge, encryptionMode) << endl;
        
        fileOut << encryptDecryptInt(contactVect[i].monthBorn, encryptionMode) << endl;
        
        fileOut << encryptDecryptInt(contactVect[i].dayBorn, encryptionMode) << endl;
        
        fileOut << encryptDecryptInt(contactVect[i].yearBorn, encryptionMode);
        
        fileOut << "\n\n";
    }
    
    fileOut << "Contacts Last Altered: " << obtainDateAndTime() << endl;
    
    fileOut.close();
} // saveContactBookAndSettings()

string obtainDateAndTime()//not my code here - modified it to display what I want and to read easier
{
    char timeArray[50];
    
    time_t now = time(NULL);
    
    strftime(timeArray, 50, "%D, %I:%M %p", localtime(&now));
    
    return string(timeArray);
} // obtainDateAndTime()
