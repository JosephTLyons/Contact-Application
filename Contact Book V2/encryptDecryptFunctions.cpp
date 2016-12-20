#include "encryptDecryptFunctions.hpp"

char encryptDecryptChar(char input, const bool &encryptionMode)//not cleaned up
{
    // USED TO ENCRYPT/DECRYPT THE VECTORS IN STRUCT: FIRSTNAME, LASTNAME, ADDRESS, PHONENUMBER, DATEOFBIRTH
    // FIRST USE A SIMPLE, HARDCODED VALUE FOR ENCRYPTION, THEN MAKE IT MORE COMPLEX
    char charKey = 'J';
    
    // ONLY ENCRYPT TEXT IF ENCRYPT MODE IS TRUE (TURNED ON), ELSE, SKIP IT AND PRINT NORMAL
    if (encryptionMode == true)
    {
        input ^= charKey;
    }
    
    return input;
} // encryptDecryptChar

int encryptDecryptInt(int input, const bool &encryptionMode)//not cleaned up
{
    /* USED TO ENCRYPT/DECRYPT INTS IN STRUCT: MONTHBORN, DAYBORN, YEARBORN AND CURRENTAGE */
    /* FIRST USE A SIMPLE, HARDCODED VALUE FOR ENCRYPTION, THEN MAKE IT MORE COMPLEX */
    /* USE A DIFFERENT METHOD OF ENCRYPTION FOR THE INTS */
    
    char intKey = 'z';
    
    /* ONLY ENCRYPT TEXT IF ENCRYPT MODE IS TRUE (TURNED ON), ELSE, SKIP IT AND PRINT NORMAL */
    
    if (encryptionMode == true)
    {
        input ^= intKey;
    }
    
    return input;
} // encryptDecryptInt
