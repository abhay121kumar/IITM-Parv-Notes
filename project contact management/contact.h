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
// size tracks how many contacts you've added so far.
// capacity is how much space you've allocated (let suppose starts at 2).
void addContact(ContactList **contacts, int *size, int *capacity);
int isDuplicate(ContactList *contacts, int size, const char *name, const char *phone);
void viewContacts(ContactList *contacts, int size);

#endif
