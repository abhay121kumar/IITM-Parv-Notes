// ------ Contact Manager ------
// 1. Add New Contact
// 2. View All Contacts
// 3. Search Contact by Name
// 4. Search Contact by Number
// 5. Update Contact
// 6. Delete Contact
// 7. Sort Contacts by Name
// 8. Exit


// _____________________________________________________________________________

//approch to achive this idea
// Step 1: Define Contact Structure
// Use struct to represent a contact with fields like name, number, email.


// Step 2: Dynamic Array of Contacts
// Start with a dynamically allocated array (via malloc) and resize it using realloc 
// when more space is needed.

// Step 3: Implement CRUD Operations
// Functions to:

// Create (add)

// Read (view/search)

// Update (edit)

// Delete contact

// Step 4: Design Modular Functions
// Each feature (add/search/delete) should be in its own function for clarity and maintainability.

// Step 5: Handle Edge Cases
// Duplicate contacts

// Case-insensitive searches

// Maximum field lengths

// No contact found

// Empty contact list

// Step 6: Optional Enhancements
// Save/load contacts to/from file

// Sort contacts alphabetically

// Validate input (e.g., number format)



// ________________________________________________________________________



// Module	Responsibility
// main.c	Main menu, user interaction
// contact.c	Core logic: add, delete, search, update
// contact.h	Struct definition and function declarations
// utils.c/h	Helper functions (string comparison, validation) -> future feature
// storage.c/h	File I/O for saving/loading contacts -> future feature







#include <stdio.h>
#include "contact.h"

int main() {
    UserChoise();  
    return 0;
}
