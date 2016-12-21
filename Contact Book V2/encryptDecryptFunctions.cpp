#include "encryptDecryptFunctions.hpp"

char encryptDecryptChar(char input)
{
    // USED TO ENCRYPT/DECRYPT THE VECTORS IN STRUCT: FIRSTNAME, LASTNAME, ADDRESS, PHONENUMBER, DATEOFBIRTH
    // FIRST USE A SIMPLE, HARDCODED VALUE FOR ENCRYPTION, THEN MAKE IT MORE COMPLEX
    
    char charKey = 'J';
    
    input ^= charKey;
    
    return input;
} // encryptDecryptChar

int encryptDecryptInt(int input)
{
    /* USED TO ENCRYPT/DECRYPT INTS IN STRUCT: MONTHBORN, DAYBORN, YEARBORN AND CURRENTAGE */
    /* FIRST USE A SIMPLE, HARDCODED VALUE FOR ENCRYPTION, THEN MAKE IT MORE COMPLEX */
    /* USE A DIFFERENT METHOD OF ENCRYPTION FOR THE INTS */
    
    int intKey = 6;
    
    input ^= intKey;
    
    return input;
} // encryptDecryptInt
