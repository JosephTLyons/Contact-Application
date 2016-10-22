#include "encryptDecryptFunctions.hpp"

char EncryptDecryptChar(char Input, const bool &EncryptionMode)//not cleaned up
{
    /* USED TO ENCRYPT/DECRYPT THE VECTORS IN STRUCT: FIRSTNAME, LASTNAME, ADDRESS, PHONENUMBER,DATEOFBIRTH */
    /* FIRST USE A SIMPLE, HARDCODED VALUE FOR ENCRYPTION, THEN MAKE IT MORE COMPLEX */
    
    char CharKey = 'J';
    
    /* ONLY ENCRYPT TEXT IF ENCRYPT MODE IS TRUE (TURNED ON), ELSE, SKIP IT AND PRINT NORMAL */
    
    if (EncryptionMode == true)
    {
        Input ^= CharKey;
    }
    
    return Input;
} // EncryptDecryptChar

int EncryptDecryptInt(int Input, const bool &EncryptionMode)//not cleaned up
{
    /* USED TO ENCRYPT/DECRYPT INTS IN STRUCT: MONTHBORN, DAYBORN, YEARBORN AND CURRENTAGE */
    /* FIRST USE A SIMPLE, HARDCODED VALUE FOR ENCRYPTION, THEN MAKE IT MORE COMPLEX */
    /* USE A DIFFERENT METHOD OF ENCRYPTION FOR THE INTS */
    
    char IntKey = 'z';
    
    /* ONLY ENCRYPT TEXT IF ENCRYPT MODE IS TRUE (TURNED ON), ELSE, SKIP IT AND PRINT NORMAL */
    
    if (EncryptionMode == true)
    {
        Input ^= IntKey;
    }
    
    return Input;
} // EncryptDecryptInt
