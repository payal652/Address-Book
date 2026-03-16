#include <stdio.h> // Include standard input-output library
#include "file.h" // Include the header file containing function declarations

// Function to save contacts to a file
void saveContactsToFile(AddressBook *addressBook) 
{
    // Open the file in write mode
    FILE *fptr=fopen("contacts.csv","w");
    // Check if the file was opened successfully
    if(fptr==NULL)
    {
        return; // Exit the function if the file could not be opened
    }
    else
    {
        // Write the total number of contacts at the beginning of the file
        fprintf(fptr,"#%d\n",addressBook->contactCount);
        // Loop through all contacts and write them to the file
        for (int i = 0; i < addressBook->contactCount; i++)
        {
            fprintf(fptr,"%s,",addressBook->contacts[i].name); // Write name
            fprintf(fptr,"%s,",addressBook->contacts[i].phone); // Write phone number
            fprintf(fptr,"%s\n",addressBook->contacts[i].email);  // Write email
        }
        //fclose(fptr); // Close the file after writing

    }
  
}
// Function to load contacts from a file
void loadContactsFromFile(AddressBook *addressBook) 
{
    // Open the file in read mode
    FILE *fptr=fopen("contacts.csv","r");
    // Check if the file exists or can be opened
    if(fptr==NULL)
    {
        return; // Exit the function if the file could not be opened
    }
    else
    {
        // Read the total number of contacts from the file
        fscanf(fptr,"#%d\n",&(addressBook->contactCount));
        // Loop through and read contact details from the file
        for (int i = 0; i < addressBook->contactCount; i++)
        {
            fscanf(fptr,"%[^,],",addressBook->contacts[i].name); // Read name until comma
            fscanf(fptr,"%[^,],",addressBook->contacts[i].phone); // Read phone number until comma
            fscanf(fptr,"%[^\n]\n",addressBook->contacts[i].email);  // Read email until newline
        }
        //fclose(fptr); // Close the file after reading

    }

    
}
