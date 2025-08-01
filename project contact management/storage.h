#ifndef STORAGE_H
#define STORAGE_H

#include "contact.h"

void saveContactsToFile(ContactList *contacts, int size);
int loadContactsFromFile(ContactList **contacts, int *capacity);
void ensureEmergencyContact(ContactList **contacts, int *size, int *capacity);

#endif
