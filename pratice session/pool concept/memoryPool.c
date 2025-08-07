#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define POOL_SIZE 10

typedef struct {
    int id;
    char name[20];
    int is_used;  // flag to check if this slot is occupied
} Customer;

// Memory pool
Customer memory_pool[POOL_SIZE];

// Allocate from pool
Customer* allocate_customer() {
    for (int i = 0; i < POOL_SIZE; i++) {
        if (!memory_pool[i].is_used) {
            memory_pool[i].is_used = 1;
            return &memory_pool[i];
        }
    }
    return NULL; // Pool full
}

// Free back to pool
void free_customer(Customer* c) {
    c->is_used = 0;
}

int main() {
    Customer* c1 = allocate_customer();
    Customer* c2 = allocate_customer();

    if (c1 && c2) {
        c1->id = 1;
        strcpy(c1->name, "Alice");

        c2->id = 2;
        strcpy(c2->name, "Bob");

        printf("Customer1: %d, %s\n", c1->id, c1->name);
        printf("Customer2: %d, %s\n", c2->id, c2->name);
    }

    free_customer(c1);
    free_customer(c2);

    return 0;
}
