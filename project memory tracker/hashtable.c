#include "hashtable.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define TABLE_SIZE 1024
extern size_t total_allocated;
extern size_t total_freed;
static MemoryBlock* hashTable[TABLE_SIZE];

static size_t hash_ptr(void* ptr) {
    return ((size_t)(ptr)) % TABLE_SIZE;
}

void ht_init() {
    memset(hashTable, 0, sizeof(hashTable));
}
//when allocating
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
    total_allocated += size; // Update total allocated size
}

// int ht_remove(void* ptr) {
//     size_t idx = hash_ptr(ptr);
//     MemoryBlock* curr = hashTable[idx];
//     MemoryBlock* prev = NULL;

//     while (curr) {
//         if (curr->address == ptr && !curr->isFreed) {
//             curr->isFreed = 1;
//             return 1; // success
//         }
//         prev = curr;
//         curr = curr->next;
//     }
//     return 0; // not found or already freed
// }

int ht_remove(void* ptr) {
    size_t idx = hash_ptr(ptr);
    MemoryBlock* curr = hashTable[idx];

    while (curr) {
        if (curr->address == ptr) {
            if (curr->isFreed) {
                printf("Warning: Double free detected at %p\n", ptr);
                return 0;
            }

            curr->isFreed = 1;
            total_freed += curr->size;  // Update total freed memory
            return 1; // success
        }
        curr = curr->next;
    }

    printf("Warning: Invalid free attempted on untracked address %p\n", ptr);
    return 0; // not found
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
    FILE* log = fopen("memory_log.txt", "a"); // append mode

    if (!log) {
        perror("Unable to open memory_log.txt");
        return;
    }


    // fprintf(log, "--- Memory Tracker Summary ---\n");
    // fprintf(log, "--- Memory Usage Stats ---\n");
    // fprintf(log, "Total Allocated: %zu bytes\n", total_allocated);
    // fprintf(log, "Total Freed:     %zu bytes\n", total_freed);
    // fprintf(log, "Memory Leaked:   %zu bytes\n", total_allocated - total_freed);

    for (int i = 0; i < TABLE_SIZE; ++i) {
        MemoryBlock* curr = hashTable[i];
        while (curr) {
            fprintf(log, "Addr=%p | Size=%zu | Type=%s | %s\n",
                    curr->address,
                    curr->size,
                    curr->type,
                    curr->isFreed ? "Freed ok" : "Leaked not freed");
            curr = curr->next;
        }
    }

    fclose(log);
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
