#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include "validation.h"

int isValidName(const char* name) {
    if (!isalpha(name[0])) return 0;
    for (int i = 0; name[i]; i++) {
        if (!isalnum(name[i])) return 0;
    }
    return 1;
}

int isValidPhone(const char* phone) {
    int i = 0;
    if (phone[0] == '+') i = 1;
    for (; phone[i]; i++) {
        if (!isdigit(phone[i])) return 0;
    }
    return i >= 10 && i <= 15;
}

int isValidEmail(const char* email) {
    const char *at = strchr(email, '@');
    const char *dot = strrchr(email, '.');

    if (!at || !dot || at > dot) return 0;

    // Validate parts before @
    for (int i = 0; email[i] && email + i < at; i++) {
        if (!isalnum(email[i])) return 0;
    }

    if (strcmp(dot, ".com") == 0 || strcmp(dot, ".in") == 0)
        return 1;

    return 0;
}
