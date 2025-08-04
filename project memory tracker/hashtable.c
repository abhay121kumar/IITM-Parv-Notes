#include "hashtable.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define TABLE_SIZE 1024

static MemoryBlock* hashTable[TABLE_SIZE];

static size_t hash_ptr(void* ptr) {
    return ((size_t)(ptr)) % TABLE_SIZE;
}

void ht_init() {
    memset(hashTable, 0, sizeof(hashTable));
}

void ht_insert(void* ptr, size_t size, const char* type) {
    size_t idx = hash_ptr(ptr);
    MemoryBlock* block = malloc(sizeof(MemoryBlock));
    block->address = ptr;
    block->size = size;
    strncpy(block->type, type, sizeof(block->type)-1);
    block->timestamp = time(NULL);
    block->isFreed = 0;
    block->next = hashTable[idx];
    hashTable[idx] = block;
}

int ht_remove(void* ptr) {
    size_t idx = hash_ptr(ptr);
    MemoryBlock* curr = hashTable[idx];
    MemoryBlock* prev = NULL;

    while (curr) {
        if (curr->address == ptr && !curr->isFreed) {
            curr->isFreed = 1;
            return 1; // success
        }
        prev = curr;
        curr = curr->next;
    }
    return 0; // not found or already freed
}

MemoryBlock* ht_find(void* ptr) {
    size_t idx = hash_ptr(ptr);
    MemoryBlock* curr = hashTable[idx];
    while (curr) {
        if (curr->address == ptr)
            return curr;
        curr = curr->next;
    }
    return NULL;
}

// void ht_dump_leaks() {
//     printf("\n--- Memory Leaks Detected ---\n");
//     for (int i = 0; i < TABLE_SIZE; ++i) {
//         MemoryBlock* curr = hashTable[i];
//         while (curr) {
//             if (!curr->isFreed) {
//                 printf("LEAK: Addr=%p | Size=%zu | Type=%s\n",
//                        curr->address, curr->size, curr->type);
//             }
//             curr = curr->next;
//         }
//     }
// }

void ht_dump_all() {
    printf("\n--- Memory Tracker Summary ---\n");
    for (int i = 0; i < TABLE_SIZE; ++i) {
        MemoryBlock* curr = hashTable[i];
        while (curr) {
            printf("Addr=%p | Size=%zu | Type=%s | %s\n",
                   curr->address,
                   curr->size,
                   curr->type,
                   curr->isFreed ? "Freed ok" : "Leaked not freed");
            curr = curr->next;
        }
    }
}


void ht_free_all() {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        MemoryBlock* curr = hashTable[i];
        while (curr) {
            if (!curr->isFreed) {
                free(curr->address); // actively free to avoid leak
            }
            MemoryBlock* tmp = curr;
            curr = curr->next;
            free(tmp);
        }
        hashTable[i] = NULL;
    }
}
