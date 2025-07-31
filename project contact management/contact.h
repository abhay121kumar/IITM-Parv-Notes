#ifndef CONTACT_H
#define CONTACT_H

#define MAX_NAME 50
#define MAX_PHONE 15
#define MAX_EMAIL 50

typedef struct {
    char name[MAX_NAME];
    char phone[MAX_PHONE];
    char email[MAX_EMAIL];
} ContactList;

// Function declarations
void UserChoise();
void addContact(ContactList **contacts, int *size, int *capacity);
void viewContacts(ContactList *contacts, int size);

#endif
