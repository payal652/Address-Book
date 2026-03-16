#ifndef CONTACT_H
#define CONTACT_H
#include<stdio.h>
#include<string.h>

#define MAX_CONTACTS 100

typedef struct Contact{
    char name[50];
    char phone[20];
    char email[50];
} Contact;

typedef struct {
    Contact contacts[MAX_CONTACTS];
    int contactCount;
} AddressBook;

void createContact(AddressBook *addressBook);
void searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook);
void initialize(AddressBook *addressBook);
void saveContactsToFile(AddressBook *AddressBook);
int phone(char* delete);
int mail(char *delete);
int validname(char* name);
int validphone(char* number,AddressBook *addressBook);
int validmail(char* mail,AddressBook *addressBook);
int searchName(AddressBook *addressBook,int arr[]);
int searchPhone(AddressBook *addressBook);
int searchEmail(AddressBook *addressBook);


#endif
