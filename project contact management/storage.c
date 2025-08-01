#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "storage.h"
#include "validation.h"

#define FILENAME "contacts.txt"

void saveContactsToFile(ContactList *contacts, int size) {
    FILE *fp = fopen(FILENAME, "w");
    if (!fp) {
        printf("Failed to open file for saving.\n");
        return;
    }

    for (int i = 0; i < size; i++) {
        fprintf(fp, "%s|%s|%s\n", contacts[i].name, contacts[i].phone, contacts[i].email);
    }

    fclose(fp);
}

int loadContactsFromFile(ContactList **contacts, int *capacity) {
    FILE *fp = fopen(FILENAME, "r");
    if (!fp) return 0; // file not found

    char line[200];
    int count = 0;

    while (fgets(line, sizeof(line), fp)) {
        if (count >= *capacity) {
            *capacity *= 2;
            *contacts = realloc(*contacts, (*capacity) * sizeof(ContactList));
        }

        line[strcspn(line, "\n")] = 0; // remove newline
        char *name = strtok(line, "|");
        char *phone = strtok(NULL, "|");
        char *email = strtok(NULL, "|");

        if (name && phone && email) {
            strncpy((*contacts)[count].name, name, MAX_NAME);
            strncpy((*contacts)[count].phone, phone, MAX_PHONE);
            strncpy((*contacts)[count].email, email, MAX_EMAIL);
            count++;
        }
    }

    fclose(fp);
    return count;
}

void ensureEmergencyContact(ContactList **contacts, int *size, int *capacity) {
    if (*size == 0) {
        ContactList emergency = {
            .name = "Emergency",
            .phone = "+91100",
            .email = "emergency@gov.in"
        };

        if (*size >= *capacity) {
            *capacity *= 2;
            *contacts = realloc(*contacts, (*capacity) * sizeof(ContactList));
        }

        (*contacts)[*size] = emergency;
        (*size)++;
        saveContactsToFile(*contacts, *size);
    }
}
