/* 
 NAME: Bijayalakshmi Patra
 BATCH: 24038
 PROJECT: 'Address Book'
 DESCRIPTION: To 1.create a contact
                 2.edit a contact
				 3.search a contact
				 4.delete a contact
				 5.list the contact 
				 6.and finally save the contact at last after doing all this criteria
*/

#include "contact.h"  // Include the header file containing function declarations
// Main function
int main()
{
	
	AddressBook addressBook; // Declare an AddressBook structure
    initialize(&addressBook); // Initialize the address book (load existing contacts if any)
	while(1) // Loop until the user chooses to exit
	{
		printf("\nAddress Book Menu:\n");
	    printf("1. Create contact\n");
	    printf("2. Search contact\n");
	    printf("3. Edit contact\n");
	    printf("4. Delete contact\n");
	    printf("5. List all contacts\n");
	    printf("6. Save and Exit\n");
	    printf("Enter your choice: ");
	    int choice;
	    scanf("%d",&choice); // Read the user's choice
		// Execute the function based on the user's choice
	    switch(choice)
		{
			case 1: createContact(&addressBook); // Call function to create a new contact
		            break;
		    case 2: searchContact(&addressBook); // Call function to search for a contact
		            break;
		    case 3: editContact(&addressBook); // Call function to edit an existing contact
		            break;
		    case 4: deleteContact(&addressBook); // Call function to delete a contact
		            break;
		    case 5: listContacts(&addressBook); // Call function to list all contacts
		            break;
		    case 6: saveContactsToFile(&addressBook); // Save contacts before exiting
			        return 0; // Exit the program
			default: printf("Invalid choice.Please select your choice (1-6)\n");
			 
	    }
	}
	return 0; // End of program
}