#include <ctype.h>    //for toupper function

#include "sortingFunctions.hpp"

void sortContactVector(vector<personalInformation> &contactVect)//my modified bubble sort code I found online//not cleaned up
{
    bool swapsMade = true;
    
    while(swapsMade)
    {
        swapsMade = false;
        
        for (int i = 0; i < contactVect.size()-1; i++)
        {
            if (!namesInOrder(contactVect[i].lastNameVector, contactVect[i + 1].lastNameVector,
                              contactVect[i].firstNameVector, contactVect[i + 1].firstNameVector))
            {
                swap(contactVect[i], contactVect[i+1]);
                
                swapsMade = true;
            }
        }
    }
} // sortContactVector()

bool namesInOrder(const vector<char> &lastNameVect1, const vector<char> &lastNameVect2,
                  const vector<char> &firstNameVect1, const vector<char> &firstNameVect2)//not cleaned up
{
    //checks to see which last name comes first
    
    for (int i = 0; lastNameVect1[i] && lastNameVect2[i]; ++i)//go until you get to the end of the larger name
    {
        if(toupper(lastNameVect1[i]) < toupper(lastNameVect2[i]))//make all uppercase to check for order
            return true;
        
        if(toupper(lastNameVect1[i]) > toupper(lastNameVect2[i]))
            return false;
    }
    
    //if both last names are the same, it then uses the first name
    
    for (int i = 0; firstNameVect1[i] && firstNameVect2[i]; ++i)//go until you get to the end of the larger name
    {
        if(toupper(firstNameVect1[i]) < toupper(firstNameVect2[i]))
            return true;
        
        if(toupper(firstNameVect1[i]) > toupper(firstNameVect2[i]))
            return false;
    }
    
    return true;//if both names are identical, return true
    //no swap will be made back in SortVector() function
} // namesInOrder()
