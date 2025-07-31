#include <stdio.h>
#include "contact.h"
#include <stdlib.h>
#include <string.h>

//add constact manager
void addContact(ContactList **contacts, int *size, int *capacity){
    //what if size is greater than capacity -> base case
    //you keep adding more, you'll need to resize (reallocate) the array if size exceeds capacity.
    if (*size >= *capacity) {
        *capacity *= 2;
        ContactList *temp = realloc(*contacts, (*capacity) * sizeof(ContactList));
        if (!temp) {
            printf("Memory allocation failed!\n");
            return;
        }
        *contacts = temp;
    }

    ContactList newContact;
    printf("Enter name: ");
    scanf(" %[^\n]", newContact.name);
    printf("Enter phone: ");
    scanf(" %[^\n]", newContact.phone);
    printf("Enter email: ");
    scanf(" %[^\n]", newContact.email);

    (*contacts)[*size] = newContact;
    (*size)++;
    printf("✅ Contact added!\n");
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
    int choice;
    while (1) {
        printf("\n--- Contact Manager ---\n");
        printf("1. Add Contact\n");
        printf("2. View Contacts\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar(); // newline

        if (choice == 1) {
            addContact(&contacts, &size, &capacity);
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