#include <iostream>

#include "mainMenuFunctions.hpp"
#include "readAndWriteFunctions.hpp"
#include "searchingFunctions.hpp"

using namespace std;

void searchForContacts(const vector<personalInformation> &contactVect, const int &displaySpeed)
{
    vector<char> criteriaToSearchFor;
    
    bool criteriaFound   = false;
    bool contactsPrinted = false;
    
    cout << "Search criteria: ";
    insertStringDataVectorFromKeyboard(criteriaToSearchFor);
    cout << "\n\n";
    
    // Look through all contacs
    for (int i = 0; i < contactVect.size(); i++)
    {
        criteriaFound = searchContactsBasedOnCriteria(contactVect[i], criteriaToSearchFor);
        
        // Display found contact/s or no contacts found
        if (criteriaFound == true)
        {
            printSingleContact(contactVect, i, displaySpeed);
            contactsPrinted = true;
        }
    }
    
    if (contactsPrinted == false)
    {
        cout << "No contacts found with this criteria.\n\n";
    }
} // searchForContacts()

bool searchContactsBasedOnCriteria(const personalInformation &contact,
                                   const vector<char> criteriaToSearchFor)
{
    // Last name check
    if (vectorsAreSame(contact.lastNameVector, criteriaToSearchFor))
        return true;
    
    // First name check
    if (vectorsAreSame(contact.firstNameVector, criteriaToSearchFor))
        return true;
    
    else
        return false;
} // searchContactsBasedOnCriteria()

// This function doesn't actually test if the vectors are identical, but actually
// Checks to see if the contact vector has at least the same string as the search vector
// I.E. If searching for "Jos", "Joseph" will return true, as it has "Jos" in it.
bool vectorsAreSame(const vector<char> &contact, const vector<char> &search)
{
    // Check each letter, but at the uppercase level so all text is the same
    // - 1 so that we dont count the newline in the vector
    for (int i = 0; i < search.size() - 1; i++)
    {
        if (toupper(contact[i]) != toupper(search[i]))
            return false;
    }
    
    return true;
} // vectorsAreSame()
