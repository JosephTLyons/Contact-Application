#include <ctype.h>    //for toupper function

#include "sortingFunctions.hpp"

void SortContactVector(vector <personalInformation> &ContactVect)//my modified bubble sort code I found online//not cleaned up
{
    bool SwapsMade = true;
    
    while(SwapsMade)
    {
        SwapsMade = false;
        
        for (int i = 0; i < ContactVect.size()-1; i++)
        {
            if (!NamesInOrder(ContactVect[i].LastNameVector, ContactVect[i+1].LastNameVector, ContactVect[i].FirstNameVector, ContactVect[i+1].FirstNameVector))
            {
                swap(ContactVect[i], ContactVect[i+1]);
                
                SwapsMade = true;
            }
        }
    }
} // SortContactVector()

bool NamesInOrder(const vector <char> &LastNameVect1, const vector <char> &LastNameVect2, const vector <char> &FirstNameVect1, const vector <char> &FirstNameVect2)//not cleaned up
{
    //checks to see which last name comes first
    
    for (int i = 0; LastNameVect1[i] && LastNameVect2[i]; ++i)//go until you get to the end of the larger name
    {
        if(toupper(LastNameVect1[i]) < toupper(LastNameVect2[i]))//make all uppercase to check for order
            return true;
        
        if(toupper(LastNameVect1[i]) > toupper(LastNameVect2[i]))
            return false;
    }
    
    //if both last names are the same, it then uses the first name
    
    for (int i = 0; FirstNameVect1[i] && FirstNameVect2[i]; ++i)//go until you get to the end of the larger name
    {
        if(toupper(FirstNameVect1[i]) < toupper(FirstNameVect2[i]))
            return true;
        
        if(toupper(FirstNameVect1[i]) > toupper(FirstNameVect2[i]))
            return false;
    }
    
    return true;//if both names are identical, return true
    //no swap will be made back in SortVector() function
} // NamesInOrder()
