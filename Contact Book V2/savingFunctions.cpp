#include <ctime>    //for time and date functions
#include <fstream>  //for reading from and saving to files
#include <iostream> //for input/output stream

#include "savingFunctions.hpp"

#include "readAndWriteFunctions.hpp"
#include "encryptDecryptFunctions.hpp"

using namespace std;

void SaveContactBookAndSettings(const vector <personalInformation> &ContactVect, const char Path[], const int &SpeedSelectionChoice, const bool &EncryptionMode)//not cleaned up
{
    ofstream FileOut;
    
    
    FileOut.open(Path);
    
    if (FileOut.fail())//check to see if file opened
        cout << "Couldn't Open File\n";
    
    
    FileOut << "Security Mode: ";
    
    FileOut << EncryptionMode << endl;
    
    FileOut << "Speed Selection Choice: ";
    
    FileOut << SpeedSelectionChoice << endl;
    
    /* SAVE NUMBER OF CONTACTS TO .TXT FILE SO WE KNOW HOW MANY WE ARE READING IN IN THE REBUILD FUNCTION */
    
    FileOut << "Number of Contacts: ";
    
    FileOut << ContactVect.size() << endl << endl;
    
    for (int i = 0; i < ContactVect.size(); i++)
    {
        /* ENCRYPTION FOR VECTORS HAPPENS IN PRINTSTRINGSTRUCT... FUNCTIONS */
        
        PrintVectorToFile(ContactVect[i].FirstNameVector, FileOut, EncryptionMode);
        
        PrintVectorToFile(ContactVect[i].LastNameVector, FileOut, EncryptionMode);
        
        PrintVectorToFile(ContactVect[i].AddressVector, FileOut, EncryptionMode);
        
        PrintVectorToFile(ContactVect[i].PhoneNumberVector, FileOut, EncryptionMode);
        
        PrintVectorToFile(ContactVect[i].DateOfBirth, FileOut, EncryptionMode);
        
        /* ENCRYPTION FOR INTS HAPPENS RIGHT HERE */
        
        FileOut << EncryptDecryptInt(ContactVect[i].CurrentAge, EncryptionMode) << endl;
        
        FileOut << EncryptDecryptInt(ContactVect[i].MonthBorn, EncryptionMode) << endl;
        
        FileOut << EncryptDecryptInt(ContactVect[i].DayBorn, EncryptionMode) << endl;
        
        FileOut << EncryptDecryptInt(ContactVect[i].YearBorn, EncryptionMode);
        
        FileOut << "\n\n";
    }
    
    FileOut << "Contacts Last Altered: " << ObtainDateAndTime() << endl;
    
    FileOut.close();
} // SaveContactBookAndSettings()

string ObtainDateAndTime()//not my code here - modified it to display what I want and to read easier
{
    char Time[50];
    
    time_t now = time(NULL);
    
    strftime(Time, 50, "%D, %I:%M %p", localtime(&now));
    
    return string(Time);
} // ObtainDateAndTime()
