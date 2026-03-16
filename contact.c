#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"
#include <ctype.h>
int indx=-1; //Declare indx as a global variable
int phone(char* del)
{
    int count=strlen(del); // calculating the length of the number string
    if(count!=10) // Phone number must be exactly 10 digits
    {
        return 0; // Invalid phone number
    }
    for(int i=0;i<count;i++)
    {
        if(!isdigit(del[i])) // Check if all characters are digits
        {
            printf("Invalid input!Please enter valid mobile number: ");
            return 0; // Invalid phone number
        }
    }
    return 1;
}
int mail(char *del)
{
    int length=strlen(del);  // calculating the length of the email string
    int flag=0,count=0;
    for(int i=0;i<length;i++)
    {
        // Check if the email contains only valid characters
        if(!islower(del[i]) && !isdigit(del[i]) && del[i] != '.' && del[i] != '@')
        {
            printf("Invalid email format! Email should contain @ and .com and digits before the @. Please enter a valid mail ID:\n");
            return 0;
        }
        if((del[i]=='@'))
        {
            count++; // Count the number of '@' characters
        }
    }
    // Check if email ends with ".com"
    if(length >= 10 && strcmp(del + length - 10, "@gmail.com") == 0) 
    {
        flag=1;
    }
    // Email should have exactly one '@' and end with ".com"
    if(count==1 && flag==1 && del[0] != '@' && del[length - 1] != '@')
    {
        return 1;
    }
    else
    {
        printf("Invalid email format.Please enter a valid mail ID:\n");
        return 0;
    }
}
int vaildname(char* name) //Function to validate a name (only alphabets and spaces allowed)
{
    for(int i=0;i<strlen(name);i++)
    {
        if(!isalpha(name[i]) && name[i]!=' ') // Check if character is not a letter or space
        {
            return 0; // Invalid name
        }
    }
    return 1; // Valid name
}

int validphone(char* number,AddressBook *addressBook) //Function to validate a phone number
{
    int count=strlen(number); // calculating the length of the number string
    if(count!=10) // Phone number must be exactly 10 digits
    {
        return 0; // Invalid phone number
    }
    for(int i=0;i<count;i++)
    {
        if(!isdigit(number[i])) // Check if all characters are digits
        {
            return 0; // Invalid phone number
        }
    }
    // Check if the phone number already exists
    for(int i=0;i<(addressBook->contactCount);i++)
    {
        if (strcmp(addressBook->contacts[i].phone,number) == 0) 
        {
            printf("Mobile number already exists!! Please enter a new mobile number:\n");
            return 0;
        }
    }
    return 1;  // Valid phone number
}
int validmailid(char* mail,AddressBook *addressBook) // Function to validate an email ID
{
    int length=strlen(mail);  // calculating the length of the email string
    int flag=0,count=0;
    for(int i=0;i<length;i++)
    {
        // Check if the email contains only valid characters
        if(!islower(mail[i]) && !isdigit(mail[i]) && mail[i] != '.' && mail[i] != '@')
        {
            
            printf("Invalid email! Email should contain @ and .com and digits before the @\n");
            printf("Please enter a valid mail ID:\n");
            return 0;
        }
        else if((mail[i]=='@'))
        {
            count++; // Count the number of '@' characters
        }
    }
    // Check if email ends with ".com"
    if(length >= 10 && strcmp(mail + length - 10, "@gmail.com") == 0) 
    {
        flag=1;
    }
    // Email should have exactly one '@' and end with ".com"
    if(count==1 && flag==1)
    {
        // Check if the email already exists
        for(int i=0;i<(addressBook->contactCount);i++)
        {
            if (strcmp(addressBook->contacts[i].email,mail) == 0) 
            {
                printf("Email already exists. Please enter a new email ID: \n");
                return 0; 
            }
        }
        return 1;  // Valid email
    }
    printf("Invalid email! Email should contain @ and .com and digits before the @\n");
    printf("Enter a valid mail ID: ");
    return 0;
}
int searchName(AddressBook *addressBook,int arr[]) // Function to search for a contact by name
{
    char str[100];
    printf("Enter the name you want to search for: ");
    int count=0; // To store the number of matching contacts
    while(1)
    {
        scanf(" %[^\n]",str); // Read full name including spaces
        if(vaildname(str)) // Validate the name
        {
            for(int i=0;i<addressBook->contactCount;i++)
            {
                if(strcmp(addressBook->contacts[i].name,str) == 0) 
                {
                    arr[count++]=i; // Store index of matching contact
                }
            }
            return count; // Return the count of found contacts
        }
        else
        {
            printf("Please enter the valid name: ");
        }
    }
}
int searchPhone(AddressBook *addressBook) // Function to search for a contact by phone number
{
    char str1[100];
    printf("Enter the mobile number: ");
    while (1) 
    {
        scanf(" %[^\n]", str1);
        if(phone(str1))  // Call the phone function to validate the mobile number
        {
            for (int i = 0; i < addressBook->contactCount; i++) 
            {
                if (strcmp(addressBook->contacts[i].phone, str1) == 0) 
                {
                    return i; // Return index if found
                }
            }
            return -1; // Return -1 if not found
        }
        else
        {
            printf("Please enter the valid mobile number: ");
        }
    }
}
int searchEmail(AddressBook *addressBook) // Function to search for a contact by mail ID
{
    char str2[100];
    printf("Enter the email ID: ");
    while (1) 
    {
        scanf(" %[^\n]", str2); 
        if (!mail(str2))  // Call the mail function to validate the email format
        {
            continue; // If the email is invalid, ask the user to enter again
        }
        for (int i = 0; i < addressBook->contactCount; i++) // If valid, proceed to search in the address book
        {
            if (strcmp(addressBook->contacts[i].email, str2) == 0) 
            {
                return i;  // Return index if found
            }
        }
        return -1;  // Email not found
    }
}
void listContacts(AddressBook *addressBook) // Function to display all contacts in the address book
{
    // Loop through all stored contacts
    printf("+----------------------+----------------+------------------------------+\n");
        printf("| %-20s | %-14s | %-28s |\n", "Name", "Phone number", "Email");
        printf("+----------------------+----------------+------------------------------+\n");
    for(int i=0;i<addressBook->contactCount;i++)
    {
        // Print the name, phone number, and email of each contact
        printf("| %-20s | %-14s | %-28s |\n", addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    printf("+----------------------+----------------+------------------------------+\n");
}
void initialize(AddressBook *addressBook) // Function to initialize the address book
{
    addressBook->contactCount = 0; // Set the initial contact count to zero
    //populateAddressBook(addressBook);
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}
void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}
void createContact(AddressBook *addressBook) // Function to create a new contact
{
    char name[20];
    printf("Enter your name: ");
    // Loop until a valid name is entered
    while(1)
    {
        scanf(" %[^\n]",name); // Read full name (including spaces)
        if(vaildname(name)) // Validate name
        {
            strcpy(addressBook->contacts[addressBook->contactCount].name,name); // Copy the entered name into the contact list
            printf("Name added successfully\n");
            break; // Exit loop if name is valid
        }
        else
        {
            printf("Invalid name!Please enter the valid name: ");
        }
    }
    char number[11];
    printf("Enter the contact number: ");
    // Loop until a valid phone number is entered
    while(1)
    {
        scanf(" %[^\n]",number); // Read the phone number input as a string
        if(validphone(number,addressBook)) // Validate phone number
        {
            strcpy(addressBook->contacts[addressBook->contactCount].phone,number); // Copy the entered phone number into the contact list
            printf("Mobile Number added successfully\n");
            break; // Exit loop if phone number is valid
        }
        else
        {
            printf("Invalid mobile number!Please enter the valid mobile number: ");
        }
    }
    char mail[20];
    printf("Enter the mail id: ");
    while(1)
    {
        scanf(" %[^\n]",mail); // Read the email input including spaces until a newline is encountered
        if(validmailid(mail,addressBook)) // Validate phone number
        {
            strcpy(addressBook->contacts[addressBook->contactCount].email,mail); // Copy the entered mail ID into the contact list
            printf("Mail ID added successfully\n");
            break; // Loop until a valid email ID is entered
        }
        /*else
        {
            printf("Invalid mail ID!Please enter the valid mail ID: ");

        }*/
    }
    addressBook->contactCount++; // Increment contact count after adding the new contact
    printf("Contact Created Successfully\n");
}
void searchContact(AddressBook *addressBook) // Function to search for a contact using name, phone number, or email ID
{
    printf("1.Search by name\n2.Search by phone number\n3.Search by email id\n4.Exit\n");
    int option;
    printf("Select one option: ");
    scanf("%d",&option);
    int arr[100]; // Array to store indexes of matching contacts
    //int index=-1;
    int count=0; // Variable to store the number of found contacts
    switch(option)
    {
        case 1: count=searchName(addressBook,arr); // function call Search by name
                break;
        case 2: indx=searchPhone(addressBook); // function call Search by phone number
                break;
        case 3: indx=searchEmail(addressBook); // function call Search by email ID
                break;
        case 4: return ; // Exit the function
        default:
                printf("Invalid option! Please enter a valid choice.\n");
    }
    // If multiple contacts were found by name
    if(count>0) 
    {
       for(int i=0;i<count;i++)
       {
        int index=arr[i]; // Get index from array
        printf("Name: %s\nPhone: %s\nEmail ID: %s\n",addressBook->contacts[index].name,addressBook->contacts[index].phone,addressBook->contacts[index].email);
       }
       searchContact(addressBook); // Ask the user to search again
    } 
    else if(indx != -1)  // If a single contact was found using phone or email
    {
        printf("Contact Found:\n");
        printf("Name: %s\nPhone: %s\nEmail ID: %s\n",addressBook->contacts[indx].name,addressBook->contacts[indx].phone,addressBook->contacts[indx].email);
        searchContact(addressBook); // Ask the user to search again
    } 
    else  // If no contact was found
    {
        printf("Contact not found!\n");
        searchContact(addressBook); // Ask the user to search again
    }
}
void editContact(AddressBook *addressBook) // Function to edit the contact in the address book
{
    int editOption; // Variable to store user choice
    char newValue[100]; // Temporary variable to store new value
    char edit[100]; // Variable to store search input
    int flag=0; // Flag to track whether contact is found
    //int indx= -1;
    printf("1. Edit Name\n2. Edit Phone Number\n3. Edit Email ID\n4. Exit Editing\n");
    printf("Select one option: ");
    scanf("%d", &editOption);
    getchar();  // Remove newline left in buffer
    switch (editOption)
    {
      case 1: while(1) // Loop until valid input
              {
                  printf("Enter the name of the contact you want to search: ");
                  scanf(" %[^\n]", edit);
                  if(vaildname(edit))
                     break; // If valid, exit loop
                  printf("Invalid name! Please enter a valid name.\n");
              }
              int count = 0;
              int arr[100]; // Array to store indexes of matching contacts
              for(int i=0;i<addressBook->contactCount;i++) // Search for contacts matching the given name
              {
                  if(strcmp(addressBook->contacts[i].name,edit)==0)
                  {
                      arr[count++] = i;
                  }
              }
              if(count == 0)
              {
                  printf("Contact not found! Cannot edit.\n");
                  editContact(addressBook); //Ask the user to edit again
                  
              }
              if(count == 1) // If exactly one contact is found, set indx
              {
                  indx = arr[0]; // Assign the only found index
                  printf("Contact Found!\n");
              }
              if(count > 1) // If multiple contacts found, ask user to narrow search
              {
                  int option;
                  printf("Multiple contacts found with the same name!\nSelect a method to identify the contact:\n");
                  printf("1. Search by Phone Number\n2. Search by Email ID\n");
                  printf("Enter your choice: ");
                  scanf("%d", &option);
                  if(option == 1)
                  {
                      char phone[20];
                      printf("Enter phone number: ");
                      scanf(" %[^\n]", phone);
                      // Search only in the found contacts
                      for(int i = 0; i < count; i++)
                      {
                          if (strcmp(addressBook->contacts[arr[i]].phone, phone) == 0)
                          {
                              indx = arr[i]; // Store the correct index to edit
                              printf("Contact Found\n");
                              break;
                          }
                      }
                  }
                  else if(option == 2) // Search using email ID
                  {
                      //indx = searchEmail(addressBook);  
                      char email[100];
                      printf("Enter email ID: ");
                      scanf(" %[^\n]", email);
                      // Search only in the found contacts
                      for(int i = 0; i < count; i++)
                      {
                          if(strcmp(addressBook->contacts[arr[i]].email, email) == 0)
                          {
                              indx = arr[i]; // Store the correct index to edit
                              printf("Contact Found\n");
                              break;
                          }
                      }
                  }
                  else
                  {
                      printf("Invalid option! Editing canceled.\n");
                      return;
                  }
              }
              if(indx == -1) // If still no contact is found
              {
                  printf("contact not found! Can't edit.\n");
                  editContact(addressBook);
              }
              else
              {
                  printf("Enter the new name: ");
                  for(int limit=1;limit<=3;limit++) // Allow 3 attempts
                  {
                      scanf(" %[^\n]",newValue);
                      if(vaildname(newValue)) // Validate new name
                      {
                          strcpy(addressBook->contacts[indx].name,newValue); // Update name
                          printf("Contact edited Successfully\n");
                          editContact(addressBook);
                          return;
                      }
                      else
                      {
                          if(limit<3)
                          {
                              printf("Invalid name You have %d attempts left. Try again\n", 3 - limit);
                              printf("Enter the name: ");
                          }
                          else
                          {
                              printf("Maximum attempts reached. name not updated.\n");
                          }
                      }
                  }
              }
              break; 
      case 2: // Editing phone number
              while (1)
              {
                  printf("Enter phone number to search the contact: ");
                  scanf(" %[^\n]", edit);
                  getchar();
                 if(phone(edit))
                    break;
                 printf("Invalid phone number! Please enter a valid 10-digit phone number.\n");
              }
               // Search for the contact using phone number
              for(int i=0;i<addressBook->contactCount;i++)
              {
                  if(strcmp(addressBook->contacts[i].phone,edit)==0)
                  {
                      flag=1; // Set flag to indicate that the contact has been found
                      indx=i; // Store the index of the found contact for editing
                      break;
                  }
              }
              if(flag==0) // If contact is not 
              {
                  printf("contact not found. Cannot edit.\n");
                  editContact(addressBook);
              }
              else
              {
                  printf("Contact Found\n");
                  printf("Enter the new mobile number: ");
                  for(int limit=1;limit<=3;limit++) // Allow 3 attempts
                  {
                      scanf(" %[^\n]", newValue);
                      if(validphone(newValue, addressBook)) // Validate new phone number
                      {
                          strcpy(addressBook->contacts[indx].phone,newValue);  // Update phone number
                          printf("Contact edited Successfully\n");
                          editContact(addressBook);
                          return;
                      }
                      else
                      {
                          if(limit<3)
                          {
                              printf("Invalid phone number You have %d attempts left. Try again\n", 3 - limit);
                              printf("Enter the phone number: ");
                          }
                          else
                          {
                              printf("Maximum attempts reached! name not updated.\n");
                          }
                      }
                  }
              }
              break;
      case 3: // Editing email ID
              while (1) 
              {
                  printf("Enter the Mail ID to search the contact: ");
                  scanf(" %[^\n]", edit);
                  getchar();
                  if(mail(edit))
                     break;
                  //printf("Invalid email format! Please enter a valid email.\n");
              }
              // Search for the contact using email ID
              for(int i=0;i<addressBook->contactCount;i++)
              {
                  if(strcmp(addressBook->contacts[i].email,edit)==0)
                  {
                      flag=1; // Set flag to indicate that the contact has been found
                      indx=i; // Store the index of the found contact for editing
                      break;
                  }
              }
              if (flag==0) // If contact is not found
              {
                  printf("contact not found! Cannot edit.\n");
                  editContact(addressBook); //function call
              }
              else
              {
                  printf("Contact Found!\n");
                  printf("Enter the new mail ID: ");
                  for(int limit=1;limit<=3;limit++) // Allow 3 attempts
                  {
                      scanf(" %[^\n]", newValue);
                      if(validmailid(newValue, addressBook)) // Validate new email
                      {
                          strcpy(addressBook->contacts[indx].email, newValue); // Update email
                          printf("Contact edited Successfully!!\n");
                          editContact(addressBook);
                          return;
                      }
                      else
                      {
                          if(limit<3)
                          {
                              printf("Invalid mail ID You have %d attempts left. Try again\n", 3 - limit);
                              printf("Enter the mail ID: ");
                          }
                          else
                          {
                              printf("Maximum attempts reached!!name not updated.\n");
                          }
                      }
                  }
              }
              break; 
      case 4: printf("Exiting editing mode!\n"); // Exit editing mode
              editOption=0;
              break;
      default:
              printf("Invalid option! Please enter a valid option.\n");   
  }                       
    // Final updated details
    printf("\nFinal updated contact:\n");
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        printf("%d. Name: %s  Phone: %s  Email: %s\n",i + 1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
}
void deleteContact(AddressBook *addressBook) // Function to delete a contact from the address book
{
    char del[100]; // Variable to store user input for contact deletion
    int flag = 0;  // Flag to check if contact is found
    int indx = -1; // Variable to store the index of the contact to be deleted
    printf("1. Delete by Name\n2. Delete by Mobile number\n3. Delete by Mail ID\n4. Exit\n");
    int option;
    printf("Select one option: ");
    scanf("%d", &option);
    getchar();
    switch(option)
    {
        case 1: 
            while(1) // Loop until valid input
            {
                printf("Enter the name of the contact to delete: ");
                scanf(" %[^\n]", del);

                if (vaildname(del)) // Validate the entered name
                    break; // If valid, exit loop

                printf("Invalid name! Please enter a valid name.\n");
            }
            int count = 0, arr[100]; // Variables to store multiple matching contacts
            for(int i = 0; i < addressBook->contactCount; i++) // Search for matching names
            {
                if(strcmp(addressBook->contacts[i].name, del) == 0)
                {
                    arr[count++] = i; // Store index of matching contact
                }
            }
            if(count == 0) // If no contacts were found
            {
                printf("Contact not found! Cannot delete.\n");
                deleteContact(addressBook); //function call
                return;
            }
            if(count > 1)   // If multiple contacts have the same name
            {
                int subOption;
                printf("Multiple contacts found with the same name.\n");
                printf("1. Search by Phone Number\n2. Search by Email ID\n");
                printf("Enter your choice: ");
                scanf("%d", &subOption);
                getchar();
                if(subOption == 1) // Search by phone number
                {
                    while(1) // Keep asking until valid phone number
                    {
                        printf("Enter phone number: ");
                        scanf(" %[^\n]", del);

                        if(phone(del))
                            break; // If valid, exit loop

                        printf("Invalid phone number! Please enter a valid 10-digit phone number.\n");
                    }
                    for(int i = 0; i < count; i++)
                    {
                        if (strcmp(addressBook->contacts[arr[i]].phone, del) == 0)
                        {
                            indx = arr[i]; // Store the correct index
                            printf("Contact Found\n");
                            break;
                        }
                    }
                }
                else if(subOption == 2) 
                {
                    while(1) // Keep asking until valid email
                    {
                        printf("Enter email ID: ");
                        scanf(" %[^\n]", del);
                        if (mail(del))
                            break; // If valid, exit loop
                        printf("Invalid mail ID!Please enter valid mail ID\n");
                    }
                    for(int i = 0; i < count; i++) // Search among matching contacts
                    {
                        if(strcmp(addressBook->contacts[arr[i]].email, del) == 0)
                        {
                            indx = arr[i]; // Store the correct index
                            printf("Contact Found\n");
                            break;
                        }
                    }
                }
                else
                {
                    printf("Invalid option! Deletion canceled.\n");
                    return;
                }
                if(indx == -1) // If no match was found
                {
                    printf("Contact not found! Cannot delete.\n");
                    deleteContact(addressBook);
                    return;
                }
            }
            else
            {
                indx = arr[0]; // If only one match was found, select it
            }
            break;
        case 2: // Delete by phone number
            while(1) // Keep asking until valid phone number
            {
                printf("Enter phone number to delete: ");
                scanf(" %[^\n]", del);
                getchar();
                if(phone(del)) // Validate phone number
                    break; // If valid, exit loop

                printf("Invalid phone number! Please enter a valid 10-digit phone number.\n");
            }
            for(int i = 0; i < addressBook->contactCount; i++)
            {
                if (strcmp(addressBook->contacts[i].phone, del) == 0)  // Search for phone number
                {
                    flag = 1;
                    indx = i; // Store index of found contact
                    printf("Contact Found\n");
                    break;
                }
            }
            if(flag == 0) // If no match found
            {
                printf("Contact not found! Cannot delete.\n");
                deleteContact(addressBook);
                return;
            }
            break;
        case 3: // Delete by email ID
            while(1) // Keep asking until valid email
            {
                printf("Enter Mail ID to delete: ");
                scanf(" %[^\n]", del);
                getchar();
                if(mail(del))
                    break; // If valid, exit loop
                //printf("Invalid email format! Please enter a valid email.\n");
            }
            for(int i = 0; i < addressBook->contactCount; i++)
            {
                if(strcmp(addressBook->contacts[i].email, del) == 0)
                {
                    flag = 1;
                    indx = i; // Store index of found contact
                    printf("Contact Found!!\n");
                    break;
                }
            }
            if(flag == 0) // If no match found
            {
                printf("Contact not found! Cannot delete.\n");
                deleteContact(addressBook); //function call
                return;
            }
            break;
        case 4: // Exit option
            return;
        default: // If invalid option is selected
            printf("Invalid option! Please enter a valid choice.\n");
            return;
    }
    if(indx != -1) // If a valid contact index is found
    {
        // Shift remaining contacts to fill the deleted contact's position
        for (int i = indx; i < addressBook->contactCount - 1; i++)
        {
            addressBook->contacts[i] = addressBook->contacts[i + 1];
        }
        addressBook->contactCount--; // Reduce contact count
        printf("Contact deleted successfully!\n");
        deleteContact(addressBook); // Prompt user for another deletion
        if(addressBook->contactCount > 0) // If there are remaining contacts, display them
        {
            printf("Remaining Contacts:\n");
            for(int i = 0; i < addressBook->contactCount; i++)
            {
                printf("%d. Name: %s  Phone: %s  Email: %s\n",i + 1, addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
            }
        }
        else
        {
            printf("No contacts left in the address book!!\n");
        }
    }
}
