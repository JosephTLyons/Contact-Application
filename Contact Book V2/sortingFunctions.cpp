#include <ctype.h>    //for toupper function

#include "sortingFunctions.hpp"

void sortContactVector(vector<personalInformation> &contactVect, const bool &lastNameFirst)
{
    // A bubble sort I found online and modified - not cleaned up
    bool swapsMade = true;
    
    while(swapsMade)
    {
        swapsMade = false;
        
        // Sort by last name first
        if (lastNameFirst == true)
        {
            for (int i = 0; i < (contactVect.size() - 1); i++)
            {
                if (!namesInOrder(contactVect[i].lastNameVector,  contactVect[i + 1].lastNameVector,
                                  contactVect[i].firstNameVector, contactVect[i + 1].firstNameVector))
                {
                    swap(contactVect[i], contactVect[i + 1]);
                    
                    swapsMade = true;
                }
            }
        }
        
        // Sort by first name first
        else
        {
            for (int i = 0; i < (contactVect.size() - 1); i++)
            {
                if (!namesInOrder(contactVect[i].firstNameVector,  contactVect[i + 1].firstNameVector,
                                  contactVect[i].lastNameVector, contactVect[i + 1].lastNameVector))
                {
                    swap(contactVect[i], contactVect[i + 1]);

                    swapsMade = true;
                }
            }
        }
    }
} // sortContactVector()

bool namesInOrder(const vector<char> &nameVect1, const vector<char> &nameVect2,
                  const vector<char> &nameVectA, const vector<char> &nameVectB)//not cleaned up
{
    //checks to see which last name comes first
    for (int i = 0; nameVect1[i] && nameVect2[i]; ++i)//go until you get to the end of the larger name
    {
        // compare letters at uppercase value to check for order
        if(toupper(nameVect1[i]) < toupper(nameVect2[i]))
            return true;
        
        if(toupper(nameVect1[i]) > toupper(nameVect2[i]))
            return false;
    }
    
    // if both names are the same, it then uses the other part of the name
    for (int i = 0; nameVectA[i] && nameVectB[i]; ++i)//go until you get to the end of the larger name
    {
        if(toupper(nameVectA[i]) < toupper(nameVectB[i]))
            return true;
        
        if(toupper(nameVectA[i]) > toupper(nameVectB[i]))
            return false;
    }
    
    //if both names are identical, return true
    //no swap will be made back in SortVector() function
    return true;
} // namesInOrder()

