#include <stdio.h>
#include "contact.h"
#include <stdlib.h>
#include <string.h>
#include "storage.h"
//add constact manager
#include "validation.h"
int isDuplicate(ContactList *contacts, int size, const char *name, const char *phone) {
    for (int i = 0; i < size; i++) {
        if (strcasecmp(contacts[i].name, name) == 0 || strcmp(contacts[i].phone, phone) == 0) {
            return 1;  // duplicate found
        }
    }
    return 0;
}
void addContact(ContactList **contacts, int *size, int *capacity) {
    ContactList newContact;
    do {
        printf("Enter name (start with letter, only letters and digits): ");
        scanf(" %[^\n]", newContact.name);
        if (!isValidName(newContact.name)) {
            printf("Invalid name. Try again.\n");
        }
    } while (!isValidName(newContact.name));

    do {
        printf("Enter phone (+digits or digits only): ");
        scanf(" %[^\n]", newContact.phone);
        if (!isValidPhone(newContact.phone)) {
            printf("Invalid phone. Try again.\n");
        }
    } while (!isValidPhone(newContact.phone));
    // Check for duplicates before adding
     if (isDuplicate(*contacts, *size, newContact.name, newContact.phone)) {
        printf("Duplicate contact found! Not added.\n");
        return;
    }

    do {
        printf("Enter email (e.g. abc123@domain.com or .in): ");
        scanf(" %[^\n]", newContact.email);
        if (!isValidEmail(newContact.email)) {
            printf("Invalid email format. Try again.\n");
        }
    } while (!isValidEmail(newContact.email));

    if (*size >= *capacity) {
        *capacity *= 2;
        ContactList *temp = realloc(*contacts, (*capacity) * sizeof(ContactList));
        if (!temp) {
            printf("Memory allocation failed!\n");
            return;
        }
        *contacts = temp;
    }

    (*contacts)[*size] = newContact;
    (*size)++;
    printf(" Contact added successfully!\n");
}


//view contact manager
void viewContacts(ContactList *contacts, int size) {
    if (size == 0) {
        printf("Contact Details are empty, No user added yet!\n");
        return;
    }
    printf("\n----- Contact List -----\n");
    for (int i = 0; i < size; i++) {
        printf("Name: %s | Phone: %s | Email: %s\n",
               contacts[i].name, contacts[i].phone, contacts[i].email);
    }
}


//user_contact_manager
void UserChoise(){
    ContactList *contacts = malloc(2 * sizeof(ContactList));
    int size = 0;
    int capacity = 2;
     // Load from file
    size = loadContactsFromFile(&contacts, &capacity);
    ensureEmergencyContact(&contacts, &size, &capacity);
    int choice;
    while (1) {
        printf("\n--- Contact Manager ---\n");
        printf("1. Add Contact\n");
        printf("2. View Contacts\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar(); 

        if (choice == 1) {
            addContact(&contacts, &size, &capacity);
            saveContactsToFile(contacts, size);  // Save after adding
        } else if (choice == 2) {
            viewContacts(contacts, size);
        } else if (choice == 3) {
            printf("Exiting Contact Manager.\n");
            break;
        } else {
            printf("Invalid choice. Try again.\n");
        }
        // break;
    }
    free(contacts);
    contacts = NULL;
}