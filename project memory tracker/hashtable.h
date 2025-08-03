#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stddef.h>
#include <time.h>

typedef struct MemoryBlock {
    void* address;
    size_t size;
    char type[10];  // "malloc", "calloc", "realloc"
    time_t timestamp;
    int isFreed;
    struct MemoryBlock* next;
} MemoryBlock;

void ht_init();
void ht_insert(void* ptr, size_t size, const char* type);
int  ht_remove(void* ptr);
MemoryBlock* ht_find(void* ptr);
void ht_dump_leaks();
void ht_free_all();

#endif 
